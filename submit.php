<?php
   require_once 'config.php';
   if( $_GET["temp_c"] || $_GET["temp_f"] || $_GET["humidity"])
   {
      $sql = "INSERT INTO sensorData (temp_c, temp_f, humidity) VALUES (?, ?, ?)";
      if($stmt = mysqli_prepare($link, $sql))
      {
          mysqli_stmt_bind_param($stmt, "sss", $_GET["temp_c"], $_GET["temp_f"], $_GET["humidity"]);
          mysqli_stmt_execute($stmt);
      }
      exit();
   }
?>
<html>
   <body>

      <form action = "<?php $_PHP_SELF ?>" method = "GET">
         Temp_C: <input type = "text" name = "temp_c" />
         Temp_F: <input type = "text" name = "temp_f" />
         Humidity: <input type = "text" name = "humidity" />
         <input type = "submit" />
      </form>

   </body>
</html>
