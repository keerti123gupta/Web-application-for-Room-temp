<?php
  require_once "config.php";
?>
<html>
<body>
  <?php
		$sql = "SELECT temp_c,temp_f,humidity FROM sensorData";
		$result = mysqli_query($link,$sql);
		if (mysqli_num_rows($result) > 0) {
			// output data of each row
			 echo "<table width='30%' align='center' style='font-size: 20px;'><tr> <th>temperature(c)</th> <th>temperature(f)</th> <th>humidity</th> </tr>";
			 while($row = mysqli_fetch_array($result))
			 {
					echo "<tr><td width=10 align='center'>" . $row['temp_c'] . "</td><td width=10 align='center' > " . $row['temp_f'] . "</td><td width=10 align='center'> " . $row['humidity'] . "</td></tr>";

			}
			echo "</table>";
		} else {
			echo "<b>No Record found</b>";
		}
		// close connection
		mysqli_close($link);
	?>
</body>
</html>
