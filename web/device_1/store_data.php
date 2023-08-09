<?php
// Database configuration 
$servername = "localhost";
$username = "u0173409_kedaireka";
$password = "fikpunhas2023";
$dbname = "u0173409_kedaireka";
 
// Create database connection 
$db = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi berhasil atau tidak
if ($db->connect_error) {
    die('Koneksi gagal: ' . $db->connect_error);
}

// Atur zona waktu ke Asia/Makassar
date_default_timezone_set('Asia/Makassar');

// Simpan data sensor ke tabel 'device_1' jika ada permintaan HTTP POST atau HTTP GET
if ($_SERVER['REQUEST_METHOD'] === 'POST' || $_SERVER['REQUEST_METHOD'] === 'GET') {
    $waktu = date('H:i:s'); // Ambil timestamp saat ini
    $water_temperature = $_REQUEST['water_temperature'] ?? '';
    $do = $_REQUEST['do'] ?? '';
    $tds = $_REQUEST['tds'] ?? '';
    $air_temperature = $_REQUEST['air_temperature'] ?? '';
    $ph = $_REQUEST['ph'] ?? '';
    $amonia = $_REQUEST['amonia'] ?? '';

    $sql = "INSERT INTO device_1 (waktu, water_temperature, do, tds, air_temperature, ph, amonia)
            VALUES ('$waktu', '$water_temperature', '$do', '$tds', '$air_temperature', '$ph', '$amonia')";

    if ($db->query($sql) === TRUE) {
        echo "Data sensor berhasil disimpan.";
    } else {
        echo "Error: " . $sql . "<br>" . $db->error;
    }
}

// Tutup koneksi
$db->close();
?>
