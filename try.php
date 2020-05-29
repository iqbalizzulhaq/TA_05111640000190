
<?php

// GET request


// Initialize connection to MySQL database
$servername = "localhost" ;
$username = "root" ;
$password = "";
$dbname = "Tugas_Akhir";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
	die("Connection failed: " . mysqli_connect_error());
}{
    echo "Connected successfully <br>";
}

if (isset($_GET['averagePingtime'])){
	$averagePingtime = $_GET['averagePingtime'];
}
else{
	echo "Data not received1";
}
if (isset($_GET['location'])){
	$location= $_GET['location'];
}
else{
	echo "Data not received6";
}

if (isset($_GET['maxPingtime'])){
	$maxPingtime = $_GET['maxPingtime'];
}
else
{
	echo "Data not received2";
}

if (isset($_GET['minPingtime'])){
	$minPingtime = $_GET['minPingtime'];
}
else
{
	echo "Data not received3";
}
if (isset($_GET['throughput'])){
	$throughput = $_GET['throughput'];
}
else
{
	echo "Data not received4";
}
if (isset($_GET['kategori'])){
	$kategori = $_GET['kategori'];
}
else
{
	echo "Data not received5";
}




//Insert into database
$data_sql = "INSERT INTO logs (id, location, averagePingtime ,maxPingtime,minPingtime,throughput,kategori, timestamp) 
VALUES ('NULL','$location', '$averagePingtime', '$maxPingtime','$minPingtime','$throughput','$kategori', NOW());";
$stmt=mysqli_query($conn, $data_sql);

//$device_list = array(); 

mysqli_close($conn);
?>