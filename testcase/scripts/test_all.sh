test_syntax_error () {
    run_syntax_test '|'
    run_syntax_test '<'
    run_syntax_test '| |'

    # run_syntax_test '< >'
    run_syntax_test '| echo'
    run_syntax_test 'echo > <'
    run_syntax_test 'echo | |'
    run_syntax_test 'echo hello > |'
    run_syntax_test 'echo hello >> |'

    # run_syntax_test 'cat < |'
    run_syntax_test 'echo hello > '
    run_syntax_test 'echo hello >>'

    # run_syntax_test 'cat < '
    run_syntax_test 'echo hello > > test1.txt'
    run_syntax_test 'echo hello >> >> test1.txt'
    run_syntax_test 'echo hello > >> test1.txt'
    run_syntax_test 'echo hello > < test1.txt'

    # run_syntax_test 'cat < < test1.txt'
    run_syntax_test 'cat << < end'
    run_syntax_test 'cat << > end'
    # run_syntax_test 'cat << | end'
    run_syntax_test 'cat <<< end'
    run_syntax_test 'echo <<< end hello'
    run_syntax_test 'cat <<<< end'

    # pipe中でbashを起動するテスト
    run_syntax_test 'echo exit | bash'

    run_syntax_test 'echo -n -n -n -n hello'
    run_syntax_test 'ls > a| echo > b > c'

    # bashでctrl+d押すとexitを出力して終わる
    # bash-3.2$ exit
}

test_command_not_found () {
    # command not found should exit with status 127
    run_test 'unknowncommand'
    run_test 'unknowncommand | commandunknown'
}

# test_paths () {
#     ### Absolute path
#     run_test '/bin/ls ; echo $?'
#     run_test '/home ; echo $?'
#     run_test '$PWD/minishell ; exit'


#     ### Relative path
#     run_test '$OLDPWD ; echo $?'
#     run_test './. ; echo $?'
#     run_test './.. ; echo $?'
#     run_test './... ; echo $?'
#     run_test 'touch aaa ; ./aaa ; rm aaa'
#     run_test 'touch bbb ; chmod +x bbb ; ./bbb ; rm bbb'
#     run_test 'mkdir ccc ; ./ccc ; rmdir ccc'
#     run_test 'mkdir ccc ; touch ccc/ddd ; chmod +x ccc/ddd ; ccc/ddd ; rm -rf ccc'
#     run_test 'touch eee ; echo "echo \$SHLVL" > eee ; echo exit >> eee ; ./minishell < eee ; rm eee'
#     run_test 'touch fff ; echo "echo \$SHLVL" > fff ; echo exit >> fff ; ././././././././minishell < fff ; rm fff'
#     run_test 'touch ggg ; echo "echo \$SHLVL" > ggg ; echo exit >> ggg ; .///././/./././minishell < ggg ; rm ggg'
#     run_test 'touch hhh ; echo "echo \$SHLVL" > hhh ; echo \$OLDPWD >> hhh ; echo exit >> hhh ; .///././/./././minishell < hhh; rm hhh'

#     run_test "mkdir ccc ; echo '#!/bin/sh' 'echo hello' > ccc/ddd ; chmod +x ccc/ddd ; ccc/ddd ; rm -rf ccc"

#     ### Environment PATH
#     run_test "cp /bin/ls a ; export PATH=: ; a ; /bin/rm a"
#     run_test "cp /bin/ls a ; export PATH=:: ; a ; /bin/rm a"
#     run_test "cp /bin/ls a ; export PATH=. ; a ; /bin/rm a"
#     run_test "cp /bin/ls ls ; unset PATH ; ls ; /bin/rm ls"
#     run_test "cp /bin/ls ls ; export PATH= ; ls ; /bin/rm ls"
#     run_test "cp /bin/ls ls ; export PATH='' ; ls ; /bin/rm ls"
# }

test_shlvl () {
    ### SHLVL
    # SHLVLV に文字列やINT_MAX, INT_MIN 以外の数字を与える
    # SHLVL の最大値は 1000
    # 1000 は表示されない
    echo
}

test_separator () {
    run_test 'echo hello'
    run_test 'echo hello world'
}

test_pipe () {
    run_test 'ls | wc | wc'
    run_test 'cat /dev/urandom | head -c 100 | wc -c'
}

test_redirections () {
    # redirection should work without command
    run_test_with_files '<test1.txt'
    run_test_with_files '<test1.txt<test2.txt<test3.txt<test4.txt'

    # < redirection shoud fail if file does not exist
    run_test 'cat < nonexistingfile'

    # > redirection
    run_test 'echo hello >>>> file'
    run_test 'cat test1 > test2 > test3'
    run_test '> f0 echo > f1 > f2 > f3 abc'
    #最後のhelloが書き込まれる
    run_test 'cat file1 > file | echo hello >> file'
    # file1の内容にhelloが追記される
    run_test 'cat file1 > file | cat file2 >> file'
    # 何も書かれない
    run_test 'cat file1 > file | echo hello >> file | cat'
}

test_quotes () {
    # quotes should work in simple use cases
    run_test "echo hello'world'foo"

    # quotes should work empty
    run_test "echo '' | cat -e"
    run_test "echo '''''' | cat -e"
    run_test "echo '' '''' | cat -e"

    # quotes should work with whitespaces
    run_test "echo '   ' | cat -e"
    run_test "echo '   ''      ''  ' | cat -e"

    # quotes should not add operators

    # quotes do not split fields
    run_test "'echo hello'"

    # Single quotes

    # single quote should preserve literal values

    # Double quotes

    # double quotes should preserve literal values

    # double quotes backslash should escape only if followed by $ " \

    # # double quotes should expand $

    # # double quotes should add empty to unknown variable
}

test_vars () {
    # $? should print exit status

    # # $? should work in sequence

    # # $? should be undefined in pipe

    # # $? should work in pipes and redirections

    ### Expansion

    # dollar sign preceding double quote

    # dollar sign should print
    run_test 'echo $'
    run_test 'echo $ $ $    $ $ $ $'

    # # dollar sign should expand

    # variable expansion should work with ;

    # variable expansion order is undefined in pipe
    run_test 'export B=bbb | echo $B | cat -e'
    run_test 'echo $B | export B=bbb | cat -e'

    # variable expansion is before redirection

    # variable expansion is before word

    # # variable expansion as special characters

    # # Quotes and Expansions are hard
}
