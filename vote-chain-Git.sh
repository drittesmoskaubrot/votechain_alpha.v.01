#!/bin/sh


_clone()  {
URL1="git clone https://github.com/drittesmoskaubrot/votechain_test_repo.git"
URL2="git clone https://github.com/drittesmoskaubrot/votechain_alpha.v.01.git"
URL3="git clone https://github.com/drittesmoskaubrot/votechain_alpha.v.02.git"

if [ "$1" -eq "0" ]
   then
   git clone https://github.com/drittesmoskaubrot/votechain_test_repo.git
   git clone https://github.com/drittesmoskaubrot/votechain_alpha.v.01.git
   git clone https://github.com/drittesmoskaubrot/votechain_alpha.v.02.git

      
fi
if [ "$1" -eq "1" ]
   then
      $URL1
fi
if [ "$1" -eq "2" ]
   then
      $URL2
fi
if [ "$1" -eq "3" ]
   then
      $URL3
fi
}

_add()  {
  if [ "$1" -eq "1" ]
   then
      cd votechain_test_repo
      git add .
      cd ..
  fi
  if [ "$1" -eq "2" ]
     then
        cd votechain_alpha.v.01
        git add .
        cd ..
  fi
  if [ "$1" -eq "3" ]
     then
        cd votechain_alpha.v.02
        git add .
        cd ..
  fi
 }
_pull() {
  if [ "$1" -eq "1" ]
   then
      cd votechain_test_repo
      git pull
      cd ..
  fi
  if [ "$1" -eq "2" ]
     then
        cd votechain_alpha.v.01
        git pull
        cd ..
  fi
  if [ "$1" -eq "3" ]
     then
        cd votechain_alpha.v.02
        git pull
        cd ..
  fi
}
_commit(){
  if [ "$1" -eq "1" ]
   then
      cd votechain_test_repo
      git commit -m$2
      cd ..
  fi
  if [ "$1" -eq "2" ]
     then
        cd votechain_alpha.v.01
        git commit -m$2
        cd ..
  fi
  if [ "$1" -eq "3" ]
     then
        cd votechain_alpha.v.02
        git commit -m$2
        cd ..
  fi
}

_push() {
  if [ "$1" -eq "1" ]
   then
      cd votechain_test_repo
     git push
      cd ..
  fi
  if [ "$1" -eq "2" ]
     then
        cd votechain_alpha.v.01
       git push
        cd ..
  fi
  if [ "$1" -eq "3" ]
     then
        cd votechain_alpha.v.02
        git push
        cd ..
  fi

   
}


if [ "$#" -eq "0" ]
   then
     SPACE="        " 
     SPACE2="       "
     printf "[*] Usage: vote-chain-Git.sh\n$SPACE -clone <repository>\n$SPACE -add <repository>\n$SPACE -pull <repository>\n$SPACE -commit <repository> <message> \n$SPACE -push <repository>\n";
     printf "$SPACE -repositories: <1,2,3>\n"
     printf "$SPACE -message: <commmit details>\n"
else
     var=$1
     if [ $var = "-clone" ]
         then
         _clone $2
     fi
      if [ $var = "-pull" ] 
         then
           _pull $2
     fi   
      if [ $var =  "-add" ] 
         then
          _add $2
     fi   
      if [ $var =  "-commit" ] 
         then
           _commit $2 $3
     fi   
      if [ $var = "-push" ] 
         then
           _push $2
     fi      
 fi
