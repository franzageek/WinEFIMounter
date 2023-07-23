
function3 ()
{
echo "You chose to proceed."
# some other code
}

function2 ()
{
    read -p “Press A to proceed or B to go back...” choice
    case $choice in
        A) 
          function1
          ;;
        B)
          function3
          ;;
    esac
}

function1 ()
{
    read -s -p "Press any key to begin..."
    function2
}

function1
