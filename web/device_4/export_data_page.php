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

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <!-- Bootstrap library -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">

    <title>Expot Data</title>
</head>
<body>
    <div class="container" style="padding : 2rem;">
        <!-- Export link -->
        <div class="d-flex justify-content-between align-items-center mb-3">
            <h1>AQUANOTES DEVICE 4</h1>
            <a href="export_data.php" class="btn btn-success"><i class="dwn"></i> Export</a>
        </div>

        <!-- Data list table -->
        <table class="table table-dark table-bordered" style="font-size: 20px;">
            <thead class="thead-dark">
                <tr>
                    <th>ID</th>
                    <th>Time</th>
                    <th>Water Temperature</th>
                    <th>Dissolved Oxygen</th>
                    <th>Turbidity</th>
                    <th>Air Temperature</th>
                    <th>pH</th>
                    <th>Amonia</th>
                </tr>
            </thead>
            <tbody class="table-light">
            <?php 
            // Fetch records from database 
            $result = $db->query("SELECT * FROM device_4 ORDER BY id ASC"); 
            if($result->num_rows > 0){ 
                while($row = $result->fetch_assoc()){ 
            ?>
                <tr>
                    <td><?php echo $row['id']; ?></td>
                    <td><?php echo $row['waktu'].' '.$row['date']; ?></td>
                    <td><?php echo $row['water_temperature']; ?></td>
                    <td><?php echo $row['do']; ?></td>
                    <td><?php echo $row['tds']; ?></td>
                    <td><?php echo $row['air_temperature']; ?></td>
                    <td><?php echo $row['ph']; ?></td>
                    <td><?php echo $row['amonia']; ?></td>
                </tr>
            <?php } }else{ ?>
                <tr><td colspan="7">No Value(s) found...</td></tr>
            <?php } ?>
            </tbody>
        </table>
    </div>
</body>
</html>