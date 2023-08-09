<?php
$servername = "localhost";
$username = "u0173409_kedaireka";
$password = "fikpunhas2023";
$dbname = "u0173409_kedaireka";

$db = new mysqli($servername, $username, $password, $dbname);
if ($db->connect_error) {
    die("Connection failed: " . $db->connect_error);
}

$start = isset($_GET['start']) ? $_GET['start'] : null;
$end = isset($_GET['end']) ? $_GET['end'] : null;
$table = isset($_GET['table']) ? $_GET['table'] : null;

$query = "SELECT * FROM $table"; // Gunakan tabel yang dipilih dari query parameter
if ($start && $end) {
    $query .= " WHERE date BETWEEN '$start' AND '$end'";
}
$query .= " ORDER BY id ASC";

$queryResult = $db->query($query);

$data = array();
if ($queryResult->num_rows > 0) {
    while ($row = $queryResult->fetch_assoc()) {
        $data[] = array(
            'id' => $row['id'],
            'waktu' => $row['waktu'],
            'date' => $row['date'],
            'water_temperature' => $row['water_temperature'],
            'do' => $row['do'],
            'tds' => $row['tds'],
            'air_temperature' => $row['air_temperature'],
            'ph' => $row['ph'],
            'amonia' => $row['amonia']
        );
    }
}

// Mengirim data dalam format JSON
header('Content-Type: application/json');
echo json_encode($data);
exit;
?>
