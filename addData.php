<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "Tugas_Akhir";
 
    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }
    else{
        echo "connection success";
    }
    echo "tes1";
    if(!empty($_GET['averagePingtime']) && !empty($_GET['maxPingtime'])&& 
    !empty($_GET['minPingtime'])&& !empty($_GET['throughput'])&& 
    !empty($_GET['kategori']))
    {   
        echo "tes2";
    	$averagePingtime = $_GET['averagePingtime'];
        $maxPingtime    = $_GET['maxPingtime'];
        $minPingtime    = $_GET['minPingtime'];
        $throughput     = $_GET['throughput'];
        $kategori       = $_GET['kategori'];
        
        echo "tes3";
	    $sql = "INSERT INTO logs (averagePingtime, maxPingtime,minPingtime,throughput,kategori)
		
		VALUES ('".$averagePingtime."', '".$maxPingtime."', ".$minPingtime."',".$throughput."',".$kategori."')";

        echo "tes4";

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
 
 
	$conn->close();
?>