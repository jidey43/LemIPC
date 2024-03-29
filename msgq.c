/*
** msgq.c for lemipc in /home/giudici/rendu/lemipc/LemIPC
** 
** Made by Giudici
** Login   <giudici@epitech.net>
** 
** Started on  Wed Mar  4 15:50:27 2015 Giudici
** Last update Fri Mar  6 17:07:52 2015 Giudici
*/

#include "lemipc.h"

int		create_msgq(t_ia *ia)
{
  int		id_msg;

  id_msg = msgget(ia->key, IPC_CREAT | SHM_R | SHM_W);
  if (id_msg == -1)
    return (-1);
  return (0);
}

int		msg_receive(t_msg *msg, t_ia *ia)
{
  int		id_msg;

  id_msg = msgget(ia->key, SHM_R | SHM_W);
  if (id_msg == -1)
    return (-1);
  msgrcv(id_msg, msg, sizeof(msg), (int)ia->team, 0);
  printf("\n\n\n\nmsg ------ x = %d && y = %d ----- \n\n\n", msg->pos.x, msg->pos.y);
  ia->target_pos.x = msg->pos.x;
  ia->target_pos.y = msg->pos.y;
  return (0);
}

int		msg_send(t_msg *msg, t_ia *ia)
{
  int		id_msg;

  id_msg = msgget(ia->key, SHM_R | SHM_W);
  if (id_msg == -1)
    return (-1);
  printf("\n\n\n\nmsg ------ x = %d && y = %d ----- \n\n\n", msg->pos.x, msg->pos.y);
  msgsnd(id_msg, msg, sizeof(msg), msg->mtype);
  msgctl(id_msg, IPC_RMID, NULL);
  return (0);
}

t_msg		construct_msg(int x, int y, int type)
{
  t_msg         msg;

  bzero(&msg, sizeof(msg));
  msg.pos.x = x;
  msg.pos.y = y;
  msg.mtype = type;
  return (msg);
}

void		free_msg()
{
  int		i;
  key_t		key;
  int		id_msg;
  char		c;

  i = 0;
  while (i != 15)
    {
      c = i;
      key = ftok(getcwd(0, 0), c);
      id_msg = msgget(key, SHM_R | SHM_W);
      if (id_msg == -1)
	puts("chelouuuu");
      msgctl(id_msg, IPC_RMID, NULL);
      i = i + 1;
    }
}
