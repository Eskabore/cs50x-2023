// Fade in the About Me section when the page loads
$(document).ready(function() {
    $(".container").hide();
    $(".container").fadeIn(1500);
  });

  // Add a hover effect to the hobby section
  $("#hobby-section").hover(function() {
    $(this).css("background-color", "#f5f5f5");
    $(this).css("color", "black");
  }, function() {
    $(this).css("background-color", "white");
    $(this).css("color", "black");
  });

  // Animate the photographs in the hobby section
  $(".img-thumbnail").hover(function() {
    $(this).animate({width: "350px", height: "350px"}, "slow");
  }, function() {
    $(this).animate({width: "250px", height: "250px"}, "slow");
  });