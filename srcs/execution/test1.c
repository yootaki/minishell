#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "../../libft/libft.h"


char	*strjoin_2times(char *path, const char *str, char *cmd)
{
	char	*tmp_path_cmd;
	char	*path_cmd;

	tmp_path_cmd = ft_strjoin(path, str);
	if (tmp_path_cmd == NULL)
		return (NULL);
	path_cmd = ft_strjoin(tmp_path_cmd, cmd);
	if (path_cmd == NULL)
	{
		free(tmp_path_cmd);
		return (NULL);
	}
	free(tmp_path_cmd);
	return (path_cmd);
}

char	*search_cmd(char *cmd, char **g_path_list)
{
	struct stat      stat_buf;
	char	*path_cmd;
	int		i;

	i = 0;
	while (g_path_list[i] != NULL)
	{
		path_cmd = strjoin_2times(g_path_list[i], "/", cmd);
		if (path_cmd == NULL)
			return (NULL);
		printf("path_cmd = %s\n", path_cmd);
		if (stat(path_cmd, &stat_buf) == 0)
		{
			if (stat_buf.st_mode & S_IXUSR)
			{
				printf("ok!\n");
				printf("path_cmd = %s\n", path_cmd);
				break ;
			}
		}
		free(path_cmd);
		i++;
	}
	if (g_path_list[i] == NULL)
		return (cmd);
	//free (cmd);
	return (path_cmd);
}

char	**search_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0 && envp[i])
		i++;
	if (envp[i] == NULL)
		exit(1);
	path = ft_split(&envp[i][5], ':');
	if (path == NULL)
	{
		perror("malloc");
		exit(1);
	}
	return (path);
}

int main(int argc, char **argv, char **envp)
{
	struct stat      stat_buf;
	char	*cmd_path;
	char	**g_path_list;
	char perm[10];

	g_path_list = search_path(envp);
	cmd_path = search_cmd(argv[1], g_path_list);

	if (argc != 2)
	{
		fprintf(stderr, "main : 実行時引数の数が不当です\n");
		exit(EXIT_FAILURE);
	}
	if (stat(cmd_path, &stat_buf) == 0) {
		/* ファイル情報を表示 */
		printf("デバイスID : %d\n",stat_buf.st_dev);
		printf("inode番号 : %llu\n",stat_buf.st_ino);
		printf("アクセス保護 : %o\n",stat_buf.st_mode);
		printf("ハードリンクの数 : %d\n",stat_buf.st_nlink);
		printf("所有者のユーザID : %d\n",stat_buf.st_uid);
		printf("所有者のグループID : %d\n",stat_buf.st_gid);
		printf("デバイスID（特殊ファイルの場合） : %d\n",stat_buf.st_rdev);
		printf("容量（バイト単位） : %lld\n",stat_buf.st_size);
		printf("ファイルシステムのブロックサイズ : %d\n",stat_buf.st_blksize);
		printf("割り当てられたブロック数 : %lld\n",stat_buf.st_blocks);
		printf("最終アクセス時刻 : %s",ctime(&stat_buf.st_atime));
		printf("最終修正時刻 : %s",ctime(&stat_buf.st_mtime));
		printf("最終状態変更時刻 : %s",ctime(&stat_buf.st_ctime));
	}
	else
	{
		perror("main ");
	}
	/*if ((stat_buf.st_mode & S_IXUSR))
		printf("access ok!\n");
	if ((stat_buf.st_mode & S_IWUSR))
		printf("Write Ok!\n");
	else
		printf("Write No!\n");*/
	for (int i = 0; i < 9; i++)
		perm[i] = '-';
	perm[9] = '\0';
	if (stat_buf.st_mode & S_IRUSR) perm[0] = 'r';
	if (stat_buf.st_mode & S_IWUSR) perm[1] = 'w';
	if (stat_buf.st_mode & S_IXUSR) perm[2] = 'x';
	if (stat_buf.st_mode & S_ISUID) perm[2] = 's';
	if (stat_buf.st_mode & S_IRGRP) perm[3] = 'r';
	if (stat_buf.st_mode & S_IWGRP) perm[4] = 'w';
	if (stat_buf.st_mode & S_IXGRP) perm[5] = 'x';
	if (stat_buf.st_mode & S_ISGID) perm[5] = 's';
	if (stat_buf.st_mode & S_IROTH) perm[6] = 'r';
	if (stat_buf.st_mode & S_IWOTH) perm[7] = 'w';
	if (stat_buf.st_mode & S_IXOTH) perm[8] = 'x';
	if (stat_buf.st_mode & S_ISVTX) perm[8] = 't';
	puts(perm);
	return (0);
}