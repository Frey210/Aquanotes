<?php
ob_end_clean(); // Clear output buffer
error_reporting(E_ALL);
ini_set('display_errors', 1);
ini_set('memory_limit', '512M');

$servername = "localhost";
$username = "u0173409_kedaireka";
$password = "fikpunhas2023";
$dbname = "u0173409_kedaireka";

$db = new mysqli($servername, $username, $password, $dbname);
if ($db->connect_error) { 
    die("Connection failed: " . $db->connect_error); 
}

$date = isset($_GET['date']) ? $_GET['date'] : null;
$start = isset($_GET['start']) ? $_GET['start'] : null;
$end = isset($_GET['end']) ? $_GET['end'] : null;

$query = "SELECT * FROM device_1";
if ($date) {
    $query .= " WHERE date = '$date'";
} elseif ($start && $end) {
    $query .= " WHERE date BETWEEN '$start' AND '$end'";
}
$query .= " ORDER BY id ASC";

$queryResult = $db->query($query);

if ($queryResult->num_rows > 0) {
    $delimiter = ",";
    $filename = "device_1_" . date('Y-m-d') . ".csv";
    $f = fopen('php://memory', 'w');
    $fields = array('ID', 'Time', 'Date', 'Water Temperature', 'Dissolved Oxygen', 'Turbidity', 'Air Temperature', 'pH', 'Amonia');
    fputcsv($f, $fields, $delimiter);

    while ($row = $queryResult->fetch_assoc()) {
        $lineData = array($row['id'], $row['waktu'], $row['date'], $row['water_temperature'], $row['do'], $row['tds'], $row['air_temperature'], $row['ph'], $row['amonia']);
        fputcsv($f, $lineData, $delimiter);
    }

    fseek($f, 0);
    header('Content-Type: text/csv');
    header('Content-Disposition: attachment; filename="' . $filename . '";');
    fpassthru($f);
} 

exit;

?>
