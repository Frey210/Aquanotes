<?php 
// Database configuration 
$servername = "localhost";
$username = "u0173409_kedaireka";
$password = "fikpunhas2023";
$dbname = "u0173409_kedaireka";
 
// Create database connection 
$db = new mysqli($servername, $username, $password, $dbname);
 
// Check connection 
if ($db->connect_error) { 
    die("Connection failed: " . $db->connect_error); 
}
 
// Fetch records from database 
$query = $db->query("SELECT * FROM device_1 ORDER BY id ASC"); 
 
if($query->num_rows > 0){ 
    $delimiter = ","; 
    $filename = "device_1_" . date('Y-m-d') . ".csv"; 
     
    // Create a file pointer 
    $f = fopen('php://memory', 'w'); 
     
    // Set column headers 
    $fields = array('ID', 'Time', 'Date', 'Water Temperature', 'Dissolved Oxygen', 'Turbidity', 'Air Temperature', 'pH', 'Amonia'); 
    fputcsv($f, $fields, $delimiter); 
     
    // Output each row of the data, format line as csv and write to file pointer 
    while($row = $query->fetch_assoc()){ 
        $lineData = array($row['id'], $row['waktu'], $row['date'], $row['water_temperature'], $row['do'], $row['tds'], $row['air_temperature'], $row['ph'], $row['amonia']); 
        fputcsv($f, $lineData, $delimiter); 
    } 
     
    // Move back to beginning of file 
    fseek($f, 0); 
     
    // Set headers to download file rather than displayed 
    header('Content-Type: text/csv'); 
    header('Content-Disposition: attachment; filename="' . $filename . '";'); 
     
    //output all remaining data on a file pointer 
    fpassthru($f); 
} 
exit; 
 
?>