(function($) {

  Drupal.behaviors.porticoStructureMap = {
    attach: function (context, settings) {

      var lat = parseFloat(settings.portico_structure.mapLat),
          lng = parseFloat(settings.portico_structure.mapLng);

      window.mapOptions = {
        zoom: 13,
        scrollwheel: false,
        // navigationControl: false,
        // mapTypeControl: false,
        // scaleControl: false,
        draggable: true,
        disableDefaultUI: true,
        center: new google.maps.LatLng(lat, lng),
      };

      var map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
      var marker = new google.maps.Marker(
        {
          position: mapOptions.center,
          map: map,
          animation: 'bounce',
        }
      );
    }
  };

})(jQuery);

function mapsInit() {

}