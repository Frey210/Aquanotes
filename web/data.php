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
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/flatpickr@4.6.9/dist/flatpickr.min.css">
    <link href="https://fonts.googleapis.com/css?family=Poppins" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet">
    <title>Export Data</title>
    <style>
        body {
            font-family: 'Poppins', sans-serif;
            background-color: #f4f6f9;
        }
        .container {
            max-width: 1000px;
            margin: 0 auto;
            padding: 2rem;
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }
        .btn-export {
            background-color: #25D366;
            border: none;
            color: white;
        }
        .btn-export:hover {
            background-color: #45a049;
        }
        #dateRange {
            background-color: #f2f2f2;
            border: none;
            border-radius: 5px;
            padding: 0.5rem;
            width: 100%;
        }
        .table-container {
            overflow-x: auto;
        }
        table {
            width: 100%;
        }
        th {
            background-color: #333;
            color: white;
            /* white-space: nowrap; */
            text-align: center;
        }
        .input-group {
            position: relative;
        }
        
        .input-group input[type="text"] {
            border-radius: 0.25rem;
        }
        
        .input-group .btn-reset {
            position: absolute;
            right: 0.5rem;
            top: 50%;
            transform: translateY(-50%);
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="d-flex justify-content-between align-items-center mb-3">
            <h1 style="font-weight : bolder;">AQUANOTES</h1>
            <a href="#" class="btn btn-success btn-export"><i class="dwn"></i> Export</a>
        </div>

        <div class="mb-3">
            <label for="tableSelector">Select Table:</label>
            <select id="tableSelector" class="form-select">
                <option value="device_1">Device 1</option>
                <option value="device_2">Device 2</option>
                <option value="device_3">Device 3</option>
                <option value="device_4">Device 4</option>
                <option value="device_5">Device 5</option>
                <option value="device_6">Device 6</option>
                <option value="device_7">Device 7</option>
                <option value="device_8">Device 8</option>
            </select>
        </div>
        
        <div class="mb-3">
            <label for="dateRange">Date Range:</label>
                <div class="input-group">
                    <input type="text" id="dateRange" class="form-control" placeholder="Select date range">
                    <div class="input-group-append">
                        <button id="filterTable" class="btn btn-primary btn-sm">Filter</button>
                        <button id="resetDateRange" class="btn btn-secondary btn-sm">Reset</button>
                    </div>
                </div>
        </div>

        <div class="mb-3">
            <label for="chartSelector">Select Chart Parameter:</label>
            <select id="chartSelector" class="form-select">
                <option value="water_temperature">Water Temperature</option>
                <option value="do">Dissolved Oxygen</option>
                <option value="tds">Turbidity</option>
                <option value="air_temperature">Air Temperature</option>
                <option value="ph">pH</option>
                <option value="amonia">Ammonia</option>
            </select>
        </div>

        <canvas id="lineChart"></canvas>
        
        <div class="table-container">
            <table class="table table-bordered" id="dataTable">
                <thead class="thead-dark">
                    <tr>
                        <th>ID</th>
                        <th>Time</th>
                        <th>Water Temperature</th>
                        <th>Dissolved Oxygen</th>
                        <th>Turbidity</th>
                        <th>Air Temperature</th>
                        <th>pH</th>
                        <th>Ammonia</th>
                    </tr>
                </thead>
                <tbody class="table-light" id="tableBody">
                    <!-- Data will be inserted here using JavaScript -->
                    <script>
                        function updateTable(data) {
                            const tableBody = document.getElementById("tableBody"); // Ambil elemen tbody dengan id "tableBody"
                            tableBody.innerHTML = ""; // Bersihkan konten tbody sebelum memasukkan data baru
                            //sasas
                            for (const row of data) {
                                const newRow = document.createElement("tr");
                                newRow.innerHTML = `
                                    <td>${row.id}</td>
                                    <td>${row.waktu} ${row.date}</td>
                                    <td>${row.water_temperature}</td>
                                    <td>${row.do}</td>
                                    <td>${row.tds}</td>
                                    <td>${row.air_temperature}</td>
                                    <td>${row.ph}</td>
                                    <td>${row.amonia}</td>
                                `;
                                tableBody.appendChild(newRow);
                            }
                        }
                    </script>
                </tbody>
            </table>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/flatpickr@4.6.9/dist/flatpickr.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script>
    // Fungsi untuk menghitung tanggal dengan offset waktu
    const adjustDateForOffset = (date, offsetInSeconds) => {
        const adjustedDate = new Date(date);
        adjustedDate.setSeconds(adjustedDate.getSeconds() + offsetInSeconds);
        return adjustedDate.toISOString();
    };

    // Definisi variabel timezoneOffset di luar event listener
    const timezoneOffset = 28800; // Offset untuk GMT+8

    // Kode Filter Tabel
    document.addEventListener("DOMContentLoaded", function() {
        const dateRangeInput = document.getElementById("dateRange");
        const filterTableButton = document.getElementById("filterTable");
        const resetDateRangeButton = document.getElementById("resetDateRange"); // Tambahkan ini
        const tableSelector = document.getElementById("tableSelector");
        const exportLink = document.querySelector(".btn-export");
        const lineChartCanvas = document.getElementById("lineChart");
        const chartSelector = document.getElementById("chartSelector");
        let currentChart = null;

        // Fungsi untuk mengupdate grafik
        function updateChart(data) {
            const selectedParameter = chartSelector.value;
            const chartLabels = data.map(row => row.waktu);
            const parameterData = data.map(row => row[selectedParameter]);

            // Event listener saat selector chart dipilih
            chartSelector.addEventListener("change", function() {
                updateChart(); // Memperbarui grafik tanpa menggunakan chartData
            });

            if (currentChart) {
                currentChart.destroy();
            }

            const chartConfig = {
                type: 'line',
                data: {
                        labels: chartLabels,
                        datasets: [
                            {
                                label: selectedParameter,
                                data: parameterData,
                                borderColor: '#25D366',
                                backgroundColor: 'rgba(0, 0, 255, 0.2)',
                                fill: false,
                            }
                        ]
                    },
                    options: {
                        scales: {
                            x: {
                                title: {
                                    display: true,
                                    text: 'Time'
                                }
                            },
                        y: {
                            title: {
                                display: true,
                                text: selectedParameter
                            }
                        }
                    }
                }
            };

            currentChart = new Chart(lineChartCanvas, chartConfig);
        }

        // Fungsi untuk memperbarui tabel
        function updateTable(data) {
            const tableBody = document.getElementById("tableBody");
            tableBody.innerHTML = "";

            for (const row of data) {
                const newRow = document.createElement("tr");
                newRow.innerHTML = `
                    <td>${row.id}</td>
                    <td>${row.waktu} ${row.date}</td>
                    <td>${row.water_temperature}</td>
                    <td>${row.do}</td>
                    <td>${row.tds}</td>
                    <td>${row.air_temperature}</td>
                    <td>${row.ph}</td>
                    <td>${row.amonia}</td>
                `;
                tableBody.appendChild(newRow);
            }
        }

        // Event listener saat tombol filter diklik
        filterTableButton.addEventListener("click", function() {
            const selectedTable = tableSelector.value;
            const startDate = dateRangeInput._flatpickr.selectedDates[0];
            const endDate = dateRangeInput._flatpickr.selectedDates[1];

            if (startDate && endDate) {
                const formattedStartDate = adjustDateForOffset(startDate, timezoneOffset);
                const formattedEndDate = adjustDateForOffset(endDate, timezoneOffset);

                const request = new XMLHttpRequest();
                const url = `get_filtered_data.php?table=${selectedTable}&start=${formattedStartDate}&end=${formattedEndDate}`;
                request.open("GET", url, true);

                request.onload = function() {
                    if (request.status >= 200 && request.status < 400) {
                        const response = JSON.parse(request.responseText);
                        updateTable(response);
                        updateChart(response); // Update grafik juga
                    } else {
                        console.error("Request error: " + request.status);
                    }
                };

                request.send();
            }
        });

        // Event listener saat tombol reset tanggal diklik
        resetDateRangeButton.addEventListener("click", function() {
            dateRangeInput._flatpickr.clear();
            updateChart(chartData);
        });

        // Kode Flatpickr
        flatpickr("#dateRange", {
            mode: "range",
            dateFormat: "Y-m-d",
            onClose: function(selectedDates, dateStr, instance) {
                const startDate = selectedDates[0];
                const endDate = selectedDates[1];
                if (startDate && endDate) {
                    const formattedStartDate = adjustDateForOffset(startDate, timezoneOffset);
                    const formattedEndDate = adjustDateForOffset(endDate, timezoneOffset);
                    const url = `export_data.php?start=${formattedStartDate}&end=${formattedEndDate}`;
                    exportLink.href = url;
                }
            }
        });

        // Event listener saat selector chart dipilih
        chartSelector.addEventListener("change", function() {
            updateChart(chartData); // Memperbarui grafik dengan data yang tersedia
        });
    });
    </script>
</body>
</html>