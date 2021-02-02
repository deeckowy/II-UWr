<!DOCTYPE HTML>
<html>
<head>
    <meta charset="utf-8"/>
    <title>Zadanie 2 lista 7</title>
    <style>
        .valid{
            border: solid green 1px;
        }
        .nonvalid{
            border: solid red 1px;
        }
    </style>
</head>
<body>
    <form name="form" action="z2l7.php" method="post">
        
    <label for="cardnum">Card number:</label><br>
        <input class="<?php 
            if(isset($_POST["cardnum"]))
            {
                $t=$_POST["cardnum"];
                if(strlen($t)!=19)
                {
                    $cardnumerr="Provided card number is too long/short!";
                    echo nonvalid;
                }
                else
                {
                    $r="/\d{4}-\d{4}-\d{4}-\d{4}/";
                    if(preg_match($r,$t))
                        echo valid;
                    else 
                    {
                        $cardnumerr="Card number contains non-digit character";
                        echo nonvalid;
                    }
                }
            }else echo "";
        ?>" type="text" id="cardnum" name="cardnum" value="<?php echo $_POST["cardnum"];?>">
        <?php 
            if(isset($cardnumerr))
                echo $cardnumerr;
        ?>
        </input><br>

        
        <label for="cardexp">Card expiration date (MM/YY):</label><br>
        <input class="<?php 
            if(isset($_POST["cardexp"]))
            {
                $t=$_POST["cardexp"];
                if(strlen($t)!=5)
                {
                    $cardexperr="Date is too long/short";
                    echo nonvalid;
                }
                else
                {
                    $r="/((0\d|1[0-2])\/[2][1-9])|([1][1-2]\/[2][0])/";
                    if(preg_match($r,$t))
                        echo valid;
                    else 
                    {
                        $cardexperr="Date contains non-digit characters!";
                        echo nonvalid;    
                    }
                }

            }
            else echo "";
        ?>"
        type="input" id="cardexp" name="cardexp" value="<?php echo $_POST["cardexp"];?>">
        <?php if(isset($cardexperr)) echo $cardexperr;?>
        </input><br>
        
        <label for="cvc">CVC:</label><br>
        <input class=
        "<?php 
            if(isset($_POST["cvc"]))
            {
                $t=$_POST["cvc"];
                if(strlen($t)!=3)
                {
                    $cvcerr="CVC is too long/short";
                    echo nonvalid;
                }
                else 
                {
                    $r="/\d{3}/";
                    if(preg_match($r,$t))
                        echo valid;
                    else 
                    {
                        $cvcerr="CVC contains non-digits characters";
                        echo nonvalid;
                    }
                }
            }else echo "";
        ?>"
        type="text" id="cvc" name="cvc" value="<?php echo $_POST["cvc"];?>">
        <?php if(isset($cvcerr))echo $cvcerr;?>
        </input><br>
        <label for="name">Name and Surname:</label><br>
        <input class=
        "<?php 
            if(isset($_POST["name"]))
            {
                $r="/[a-zA-Z]+\ [a-zA-Z]+/";
                if(preg_match($r,$_POST["name"]))
                    echo valid;        
                else 
                {
                    $namerr="Forbidden characters in name/surname";
                    echo nonvalid;
                }
            }else echo "";
        ?>"
        type="text" id="name" name="name" value="<?php 
            echo $_POST["name"];
        ?>"> <?php if(isset($namerr))echo $namerr; ?>
        </input><br>
        <label for="email">Mail adress:</label><br>
        <input class=
        "<?php 
            if(isset($_POST["email"]))
            {
                if(filter_var($_POST["email"], FILTER_VALIDATE_EMAIL))
                    echo valid;
                else
                {
                    echo nonvalid;
                    $emailerr="Email is not valid";
                }
            }else echo "";
        ?>"
        type="text" id="email" name="email" value="<?php echo $_POST["email"];?>"><?php if(isset($emailerr)) echo $emailerr;?>
        </input><br>
        <label for="phone">Phone number (xxx-xxx-xxx):</label><br>
        <input class=
        "<?php
            if(isset($_POST["phone"]))
            {
                $t=$_POST["phone"];
                if(strlen($t)!=11)
                {
                    $phonerr="Phone number is too short/long";
                    echo nonvalid;
                }
                else
                {
                    $r="/\d{3}-\d{3}-\d{3}/";
                    if(preg_match($r,$t))
                        echo valid;
                    else 
                    {
                        $phonerr="Phone number contains non-digits characters!";
                        echo nonvalid;    
                    }
                }
            }else echo "";
        ?>"type="text" id="phone" name="phone" value="<?php echo $_POST["phone"];?>">
        <?php if(isset($phonerr))echo $phonerr;?></input><br>
        <label for="amount">Amount:</label><br>
        <input class=
        "<?php
            if(isset($_POST["amount"]))
            {
                $r="/(\d+)|(\d+,\d{2})/";
                if(preg_match($r,$_POST["amount"]))
                    echo valid;
                else 
                {
                    echo nonvalid;
                    $amerr="Amount is incorrect!";
                }
            }else echo "";
        ?>"
        type="text" id="amount" name="amount" value=<?php echo $_POST["amount"];?>>
        <?php if(isset($amerr)) echo $amerr;?></input><br>
        <input type="submit" value="Send" />
    </form>
</body>

</html>
