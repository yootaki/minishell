#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char			pathname[512];
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;

	//カレントディレクトリのパスを取得
	getcwd(pathname, 512);

	//カレントディレクトリをopen
	dp = opendir(pathname);

	//openしたディレクトリ内容を読み込み
	while ((dirp = readdir(dp)) != NULL)
	{
		//dirpディレクトリの情報を取得
		stat(dirp->d_name, &buf);
		printf("%s\n", dirp->d_name);
		if (S_ISREG(buf.st_mode))
			printf("%s is file\n", dirp->d_name);
		else if (S_ISDIR(buf.st_mode))
			printf("%s is dir\n", dirp->d_name);
	}

	return (0);
}
