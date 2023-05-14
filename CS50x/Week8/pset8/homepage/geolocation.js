// Geolocation
if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(showPosition);
  } else {
    document.getElementById("location").innerHTML = "Geolocation is not supported by this browser.";
  }

  function showPosition(position) {
    var lat = position.coords.latitude;
    var lng = position.coords.longitude;
    document.getElementById("location").innerHTML = "Latitude: " + lat + "<br>Longitude: " + lng;
  }