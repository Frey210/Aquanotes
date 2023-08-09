<?php
// Define your database connection parameters
$servername = "localhost";
$username = "u0173409_kedaireka";
$password = "fikpunhas2023";
$dbname = "u0173409_kedaireka";

// Create a connection
$db = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($db->connect_error) {
    die("Connection failed: " . $db->connect_error);
}

// Array of tables to be truncated
$tables = array("device_1", "device_2", "device_3", "device_4", "device_5", "device_6", "device_7", "device_8");

foreach ($tables as $table) {
    $sql = "TRUNCATE TABLE " . $table;

    if ($db->query($sql) === TRUE) {
        echo "Table $table truncated successfully.<br>";
    } else {
        echo "Error truncating table $table: " . $db->error . "<br>";
    }
}

$db->close();
?>
