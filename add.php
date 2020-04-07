<?php
    include('koneksi.php');
 
    $wifi_ping = $_GET['i'];
 
    $sql = "INSERT INTO wifi(pingtime)  VALUES (:pingtime)";
 
    $stmt = $PDO->prepare($sql);
 
    $stmt->bindParam(':pingtime', $wifi_ping);
 
    if($stmt->execute()) {
        echo "sukses gaes";
    }else{
        echo "gagal gaes";
    }
?>