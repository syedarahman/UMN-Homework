<?php
    echo"<br><br>";
    $file=file_get_contents('center.json');
    $json=json_decode($file,true);
    echo"<br>Center parsed in:<br>";
    echo var_dump($json);

    // Parse PointsA and PointsB
    $pointsAfile = file_get_contents('pointsA.json');
    $jsonPointsA = json_decode($pointsAfile, true);

    $pointsBfile = file_get_contents('pointsB.json');
    $jsonPointsB = json_decode($pointsBfile, true);

    // $pairs = array();

    // CALCULATE EUCLIDEAN DISTANCE AND STORE PAIRS IN NEW ARRAY
    //
    // foreach($jsonPointsA['locations'] as $point_a) {
    //     $min_distance = 1000000000;
    //     $close_point;
    //     $min_index = -1;
    //     $index = 0;
    //     foreach($jsonPointsB['locations'] as $point_b) {
    //         if (!in_array($point_b,$pairs) && distance($point_a,$point_b) < $min_distance) {
    //             $min_distance = distance($point_a,$point_b);
    //             $close_point = $point_b;
    //             $min_index = $index;
    //         }
    //         $index = $index+1;
    //     }
    //     $pairs[] = $point_a;
    //     $pairs[] = $close_point;
    // }

?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Hw 6</title>
        <link rel="stylesheet" type="text/css" href="rahm0107plot.css">
        <script type="text/javascript" src="http://code.jquery.com/jquery-latest.min.js"></script>    
    </head>

    <body onload="initMap()">
        <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDoyL0NZxsBXKBteiNIWDA_vRqVMW26nbU&signed_in=true&callback=initMap" async defer></script>
        <script type="text/javascript">

            // center coords.
            jvalues = JSON.parse('<?php echo json_encode($json); ?>');
            var map;
            var center = parseFloat(jvalues['zoom']);
            var lat = parseFloat(jvalues['center']['lat']);
            var lon = parseFloat(jvalues['center']['long']);

            function initMap() {
                map = new google.maps.Map(document.getElementById('map'), {
                    center: {lat: lat, lng: lon},
                    zoom: center,
                });
                jvaluesA = JSON.parse('<?php echo json_encode($jsonPointsA); ?>');  
                var latA = parseFloat(jvaluesA['locations']['lat']);
                var lonA = parseFloat(jvaluesA['locations']['long']);
                                
                $(document).ready(function() {
                $.getJSON("pointsA.json", function(json1) {
                  $.each(json1.locations, function(key, data) {
                    var latLng = new google.maps.LatLng(data.lat, data.long); 
                        var marker = new google.maps.Marker({
                        position: latLng,
                        title: data.title
                    });
                    marker.setMap(map);
                        });
                        });
                });

                $(document).ready(function() {
                $.getJSON("pointsB.json", function(json2) {
                  $.each(json2.locations, function(key, data) {
                    var latLng = new google.maps.LatLng(data.lat, data.long); 
                        var marker = new google.maps.Marker({
                        position: latLng,
                        title: data.title
                    });
                    marker.setMap(map);
                        });
                        });
                });
            } // close init

            // DRAW POLYLINES ON MAP USING PAIRS FROM ARRAY
            //
            // function placeLines(map) {
            //     var index;
            //     var line;
            //     var color = 0;
            //     for(index = 0; index < pairs.length; index += 2) {
            //         line = new google.maps.Polyline({
            //         path: [{lat:parseFloat(pairs[index  ]['lat']),lng:parseFloat(pairs[index  ]['long'])},
            //  {lat:parseFloat(pairs[index+1]['lat']),lng:parseFloat(pairs[index+1]['long'])}],
            //             geodesic: true,
            //             strokeColor: colors[color],
            //             strokeOpacity: 1.0,
            //           strokeWeight: 2
            //         });
            //         line.setMap(map);
            //         if(color == 2){
            //             color = -1;
            //         }
            //         color++;
            //     }
            // }

            
        </script>

    <!-- Title -->
    <h1>HW 6</h1> <br>
    <!-- Navigation bar -->
    <div id="navigationBar">
        <nav>
            <a href="rahm0107plot.php">Google Map for part 1 of hw</a> |
            <a href="adRotator.html">Slideshow for part 2 of hw</a>
        </nav>
    </div><br><br>
    <!-- map  -->
    <div id="map" style="width: 800px; height: 500px;"></div>
     <br><br><br>
</body>
</html>



