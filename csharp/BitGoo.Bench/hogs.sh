hogs=('typora' 'firefox' 'code' 'ionide' 'omnisharp')

function kill_hogs() {
    echo $1
    for i in $hogs
    do
      echo kill -$1 $(pgrep -if $i)
      kill -$1 $(pgrep -if $i)
    done
}

freeze_hogs() {
    echo Freezing...
    kill_hogs 'STOP'
}

thaw_hogs() {
    kill_hogs 'CONT'
}


