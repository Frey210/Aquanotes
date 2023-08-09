var amChart; // Global variable to hold the chart instance


// Update the chart with new data
function updateamChart(data) {
    var labels = [];
    var amValues = [];

    for (var i = data.length - 1; i >= 0; i--) {
        labels.push(data[i].waktu);
        amValues.push(data[i].amonia);
    }

    var ctx = document.getElementById('sensorChart').getContext('2d');

    // Destroy existing chart if it exists
    if (amChart) {
        amChart.destroy();
    }

    // Create a new chart
    amChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: 'Amonia Parameter',
                data: amValues,
                borderColor: '#25D366',
                fill: false
            }]
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
                        text: 'Amonia (mg/L)'
                    },
                    min: 0, // Minimum value for y-axis
                    max: 5, // Maximum value for y-axis
                    stepSize: 0.5, // Interval between ticks on y-axis
                }
            }
        }
    });
}



        // Fetch data from the server
        function fetchData() {
            $.ajax({
                url: 'get_sensor_data.php',
                type: 'GET',
                dataType: 'json',
                success: function(data) {
                    console.log('Data fetched:', data);
                    updateamChart(data);
                },
                error: function(xhr, status, error) {
                    console.error('Error fetching data:', error);
                }
            });
        }

        // Fetch data initially and set interval for updates
        fetchData();
        setInterval(fetchData, 5000); // Fetch data every 5 seconds