<?php

session_start();

function getIPAddress() 
{  
    // Check if IP is from the shared internet
    if (!empty($_SERVER['HTTP_CLIENT_IP'])) 
    {  
        $ip = $_SERVER['HTTP_CLIENT_IP'];  
    }  
    // Check if IP is from the proxy
    elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) 
    {  
        $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];  
    }  
    // Check if IP is from the remote address
    else
    {  
        $ip = $_SERVER['REMOTE_ADDR'];  
    }  
    return $ip;  
}  

$ip = getIPAddress();  
echo 'User Real IP Address - ' . $ip;  

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = htmlspecialchars($_POST['username']);
    $password = htmlspecialchars($_POST['password']);

    $correct_username = "admin";
    $correct_password = "password123";

    // Validate the credentials
    if ($username == $correct_username && $password == $correct_password) {
        // If credentials are correct, store a session variable and redirect to a protected page
        $_SESSION['loggedin'] = true;
        $_SESSION['username'] = $username;
        header("Location: ../index.html");
        exit;
    } else {
        // If credentials are incorrect, display an error message
        echo "Invalid username or password!";
    }
}
?>
