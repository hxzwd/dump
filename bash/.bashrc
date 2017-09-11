# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

#Some user vars
GOBIN="/usr/local/go/bin"
GOSRC="/home/hjk/go/src"
UHOME="/home/hjk"
QPRJD="/home/hjk/qt_projects"
CODED="/home/hjk/code"
UIRD="/home/hjk/code/sem6/uir"
SEM6D="/home/hjk/code/sem6"
RBCODE="/home/hjk/rbcode"
NIXAD="/home/hjk/unix_a"
DOWNLOADS="/home/hjk/Загрузки"
QT56="/home/hjk/Qt5.6.1"
QTC56="/home/hjk/Qt5.6.1/Tools/QtCreator"
QTCB56="/home/hjk/Qt5.6.1/Tools/QtCreator/bin"
SHCODE="/home/hjk/shcode"
SSDIR="/home/hjk/session"
SSU="/home/hjk/session/utils"
SSI="/home/hjk/session/info"
SSL="/home/hjk/session/log"
SSD="/home/hjk/session/dump"
BLDD="/home/hjk/build"
WEBFILES="/home/hjk/webfiles"
WEBDATA="/home/hjk/webdata"
TUTORSDIR="/home/hjk/tutors"
CURRENT_PATH=""

DEFAULT_SCRIPTS_DIR="/home/hjk/webdata/scripts/"

#End some user vars

IPY="/usr/bin/ipython"

#Info and help
alias mhlp='cat $SSI/myhelp2.txt'
alias myhelp2='cat $SSI/myhelp2.txt'
alias sublmh2='subl ~/session/info/myhelp2.txt >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias nanomh2='nano ~/session/info/myhelp2.txt' 

#Work with Archives
alias mutgz='tar -xf'
alias mtgz='tar -cvzf'
alias mtgf='tar -tf'
alias mtgfd='tar -tvf'
alias muzip='/home/hjk/session/utils/./aunzip.py'
alias mzip='/home/hjk/session/utils/./azip.py'
alias mzipf='unzip -l'

#Jump between directories
alias cdcp='CURRENT_PATH="$(pwd)" && cd'
alias cdback='cd $CURRENT_PATH'
alias shcp='echo $CURRENT_PATH'

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'
# -> Предотвращает случайное удаление файлов.
alias mkdir='mkdir -p'

alias h='history'
alias j='jobs -l'
alias r='rlogin'
alias which='type -all'
alias ..='cd ..'
alias path='echo -e ${PATH//:/\\n}'
alias print='/usr/bin/lp -o nobanner -d $LPDEST'   # Предполагается, что LPDEST определен
alias pjet='enscript -h -G -fCourier9 -d $LPDEST'  # Печать через enscript
alias background='xv -root -quit -max -rmode 5'    # Положить картинку в качестве фона
alias du='du -kh'
alias df='df -kTh'

# Различные варианты 'ls' (предполагается, что установлена GNU-версия ls)
alias la='ls -Al'               # показать скрытые файлы
alias ls='ls -hF --color'       # выделить различные типы файлов цветом
alias lx='ls -lXB'              # сортировка по расширению
alias lk='ls -lSr'              # сортировка по размеру
alias lc='ls -lcr'              # сортировка по времени изменения
alias lu='ls -lur'              # сортировка по времени последнего обращения
alias lr='ls -lR'               # рекурсивный обход подкаталогов
alias lt='ls -ltr'              # сортировка по дате
alias lm='ls -al |more'         # вывод через 'more'
alias tree='tree -Csu'          # альтернатива 'ls'
alias chi='chromium-browser --incognito >> ~/session/dump/logs/chromium.log 2> ~/session/dump/logs/chromium.log &'
alias chni='chromium-browser >> ~/session/dump/logs/chromium.log 2> ~/session/dump/logs/chromium.log &'
#alias ipye='OLDPATH="$(pwd)" && cd ~/pycode/ipy_dir && ./ipy.sh --return=$OLDPATH'
alias ipye='OLDPATH="$(pwd)" && cd ~/pycode/ipy_dir && ./ipy.sh && cd $OLDPATH'
alias bpye='cd ~/pycode/bpy_dir && ./bpy.sh'
alias shc='source ~/.bashrc'
alias gtrm='gnome-terminal >> ~/session/dump/logs/gnome-terminal.log 2> ~/session/dump/logs/gnome-terminal.log &'
alias xtrm='xterm >> ~/session/dump/logs/xterm.log 2> ~/session/dump/logs/xterm.log &'
alias utrm='uxterm >> ~/session/dump/logs/uxterm.log 2> ~/session/dump/logs/uxterm.log &'
alias sublrc='subl ~/.bashrc >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias sublss='subl ~/session/session.sh >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias sublar='subl ~/session/autorun.py >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias sublxr='subl ~/.Xresources >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias sublmh='subl ~/session/info/myhelp.txt >> ~/session/dump/logs/subl.log 2> ~/session/dump/logs/subl.log &'
alias nanorc='nano ~/.bashrc'
alias nanoss='nano ~/session/session.sh'
alias nanoar='nano ~/session/autorun.py'
alias nanoxr='nano ~/.Xresources'
alias nanomh='nano ~/session/info/myhelp.txt'
alias myhelp='cat ~/session/info/myhelp.txt'
alias testalias='OLDPATH="$(pwd)" && echo testalias'
alias mcfar='mc --skin=darkfar -a --xterm'
alias mc='mcfar'
alias mlenv='OLDPATH="$(pwd)" && cd ~/matlabcode && ./mlenv.sh && cd $OLDPATH'
alias setalias='/home/hjk/session/utils/./aalias.py'
alias msubl='/home/hjk/session/utils/./asubl.py'
#Insert place
alias testalias3='echo I am test alias numer 3 && echo 0'
alias testalias2='echo This is testalias2'

alias tutorlist='ls -la ~/tutors/ | grep -E "[a-zA-Z0-9]*\.[a-zA-Z0-9]+" -o | grep -E "^[^\.]*" -o'
alias tutor='/home/hjk/session/utils/./tutor.py'
alias showscriptsdir='echo $DEFAULT_SCRIPTS_DIR'
alias scriptslist='tmp=`ls -la $DEFAULT_SCRIPTS_DIR` && tmp=${tmp//" "/"@"} && echo "$tmp" | grep -E "[^\@]*\.sh" -o | grep -E "^[^\.]*" -o -n'
alias script='/home/hjk/session/utils/./script.py'
alias mce='mc -e'

MATLABROOT=/home/hjk/qt_projects/MATLAB
export MATLABROOT
LD_LIBRARY_PATH=$MATLABROOT/bin/glnxa64:$MATLABROOT/sys/os/glnxa64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
PATH=$MATLABROOT/bin:$PATH  
export PATH

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi


#Start session.sh
#Set up some parameters
#Run ~/session/autorun.py script

~/session/./session.sh
