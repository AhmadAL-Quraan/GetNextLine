/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqoraan <aqoraan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2026/01/01 19:46:19 by aqoraan           #+#    #+#             */
/*   Updated: 2026/01/07 20:11:00 by aqoraan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char *free_all(char *temp, char **full_string) {
  if (*full_string) {
    free(*full_string);
    *full_string = NULL;
  }
  if (temp)
    free(temp);
  return (NULL);
}

static void cut(int *idx, char **full_string, char *new_string) {
  while ((*full_string)[*idx] && (*full_string)[*idx] != '\n') {
    new_string[*idx] = (*full_string)[*idx];
    (*idx)++;
  }
  if ((*full_string)[*idx] == '\n')
    new_string[*idx] = (*full_string)[*idx];
}

static char *give_the_line(char **full_string) {
  int idx;
  char *new_string;

  if (!full_string)
    return (NULL);
  idx = 0;

  /* FIXED POINTER USAGE */
  while ((*full_string)[idx] && (*full_string)[idx] != '\n')
    idx += 1;

  if ((*full_string)[idx] == '\n')
    idx += 1;

  new_string = malloc(idx + 1);
  if (!new_string)
    return (NULL);
  idx = 0;
  cut(&idx, full_string, new_string);

  char *temp = ft_substr(*full_string, idx + 1, ft_strlen(*full_string) - idx);
  if (*temp == 0) {
    free(temp);
    temp = NULL;
  }

  free(*full_string);
  *full_string = temp;

  new_string[idx] = '\0';
  return (new_string);
}

char *get_next_line(int fd) {
  char *ptr;
  static char *full_string;
  char *temp;
  int bytes_of_read;
  char *new_line;

  if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0)
    return (NULL);
  temp = malloc(BUFFER_SIZE + 1);
  if (!temp)
    return (NULL);
  // printf("I'm full_string before: %s\n", full_string);
  if (!full_string)
    full_string = ft_strdup("");

  bytes_of_read = 1;
  while (bytes_of_read > 0) {
    bytes_of_read = read(fd, temp, BUFFER_SIZE);
    if (bytes_of_read <= 0)
      return free_all(temp, &full_string);

    temp[bytes_of_read] = '\0';
    //    printf("Here temp: %s\n", temp);
    ptr = ft_strjoin(full_string, temp);
    free(full_string);
    full_string = ptr;
    if (ft_strchr(full_string, '\n'))
      break;
  }

  // printf("I'm full_string after: %s\n", full_string);

  new_line = give_the_line(&full_string);

  /* FIXED MEMORY LEAK */
  free(temp);
  return (new_line);
}

int main() {
  int fd = open("file.txt", O_RDONLY);
  printf("%s\n", get_next_line(fd));
  printf("%s\n", get_next_line(fd));
  printf("%s\n", get_next_line(fd));
}
