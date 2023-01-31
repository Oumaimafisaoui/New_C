/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:55:40 by oufisaou          #+#    #+#             */
/*   Updated: 2023/01/31 17:19:02 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void generate_3d(t_all *cub)
{
     int w;
     int h,bits_per_pixel,line_length,endian;
     int i;
     i = 0;
     void * img = mlx_xpm_file_to_image(cub->mlx, "parsing/xpmfile/wall4.xpm", &w, &h);
     if (!img)
     {
          printf("Error xpm file\n");
          exit(1);
     }
     unsigned int *adr1 = (unsigned int *)mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian); 
     while(i < cub->var_d.num_rays)
     {
          cub->three.d_player_pro = (WINDOW_W / 2) / tan(FEILD / 2);
          cub->ray[i].angle = fmod(cub->ray[i].angle,(2 * M_PI));
          cub->three.ray_distance = cub->ray[i].distance * (cos(cub->ray[i].angle - cub->player.ang));
          cub->ray[i].angle = fmod(cub->ray[i].angle,(2 * M_PI));
          cub->three.wall_projection = (CUBE / cub->three.ray_distance) * cub->three.d_player_pro;
          cub->ray[i].angle = fmod(cub->ray[i].angle,(2 * M_PI));
         
          int wall_height = cub->three.wall_projection;
          double wall_top_pix = (WINDOW_H / 2) - (wall_height / 2);

          double wall_bott_pix = (WINDOW_H / 2) + (wall_height / 2);
          for (int x = 0; x < wall_top_pix; x++)
          {
                my_mlx_pixel_put3(cub, i, x, create_trgb(1 ,cub->map.r_C, cub->map.g_C, cub->map.b_C));
          }
 
           double j = wall_top_pix;
          double o_x;
          
          if (cub->ray[i].hor == true)
               o_x = fmod(cub->ray[i].x , CUBE);
          else
               o_x = fmod(cub->ray[i].y , CUBE);
          // printf("->%d\n", (int)o_x);
          // printf("%f\n", o_x);
          o_x = o_x / CUBE * w; //hasroha bin l 0 w l wall instead of the TTL
          // printf("%d\n", bits_per_pixel / 8);
          // printf("%d\n", line_length);
          double save = wall_top_pix;
          double o_y;
          while (j < wall_bott_pix)
          {
               o_y = ((j - save) * h) / wall_height;
               // printf("-->%d\n", (int)o_y);
               my_mlx_pixel_put3(cub, i, (int)j, *((int *)(adr1 + ((int)o_y * w + ((int)o_x)))));
               j++;
          }
          // int f = 0;int k = 0;
          // double j = wall_top_pix;
          // while (j < wall_bott_pix  && f < 10)
          // {
          //      k = 0;
          //      while (k < (wall_bott_pix - wall_top_pix) / 10)
          //      {
          //           my_mlx_pixel_put3(cub, i, (int)j + k, *(adr1 +  (int)(f * 10 + fmod( cub->ray[i].x + cub->ray[i].y, 10)) ));
          //           k++;
                    
          //      }
          //      f++;
          //      j += (wall_bott_pix - wall_top_pix) / 10;
              
          // }
          for(int y = wall_bott_pix; y < WINDOW_H; y++)
          {

               my_mlx_pixel_put3(cub, i, y, create_trgb(1 ,cub->map.r_F, cub->map.g_F, cub->map.b_F));
          }
          i++;
     }
}