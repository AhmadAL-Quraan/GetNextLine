/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqoraan <aqoraan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:46:19 by aqoraan           #+#    #+#             */
/*   Updated: 2026/01/01 23:31:59 by aqoraan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char *free_all(char *temp, char *full_string) {
  free(temp);
  free(full_string);
  return (NULL);
}

static char *give_the_line(char *full_string) {
  int idx;

  if (!full_string) {
    return (NULL);
  }
  idx = 0;
  while (full_string[idx] && full_string[idx] != '\n') {
    idx += 1;

    if (full_string[idx] == '\n') {
      idx += 1;
      break;
    }
  }
  char *new_string = malloc(idx + 1);
  if (!new_string)
    return NULL;
  idx = 0;
  while (full_string[idx] != '\n')
    new_string[idx] = full_string[idx++];
  if (full_string[idx] == '\n')
    new_string[idx] = full_string[idx++];

  new_string[idx] = '\0';
  return new_string;
}

char *get_next_line(int fd) {
  char *ptr;
  static char *full_string;
  char *temp;
  int check1;
  int bytes_of_read;
  char *new_line;

  if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
    return (NULL);
  temp = malloc(BUFFER_SIZE);
  if (!temp)
    return (NULL);
  check1 = (ft_strchr(full_string, '\n') || full_string == NULL);
  bytes_of_read = read(fd, temp, BUFFER_SIZE);
  if (bytes_of_read <= 0)
    return (free_all(temp, full_string));
  while (bytes_of_read > 0 && check1) {
    full_string = ft_strjoin(full_string, temp);
    full_string[bytes_of_read] = '\0';
    check1 = (ft_strchr(full_string, '\n') && full_string != NULL);
    bytes_of_read = read(fd, temp, BUFFER_SIZE);
    if (bytes_of_read <= 0)
      return (free_all(temp, full_string));
  }
  new_line = give_the_line(full_string);
}
