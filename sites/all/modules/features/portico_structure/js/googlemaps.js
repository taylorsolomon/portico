(function($) {

  Drupal.behaviors.porticoStructureMap = {
    attach: function (context, settings) {

      var mainLocationLat    =  parseFloat(settings.portico_structure.mapLat),
          mainLocationLng    =  parseFloat(settings.portico_structure.mapLng),
          eveningLocationLat =  parseFloat(38.885304),
          eveningLocationLng =  parseFloat(-77.097519);

      window.mapOptions = {
        zoom: 13,
        scrollwheel: false,
        // navigationControl: false,
        // mapTypeControl: false,
        // scaleControl: false,
        draggable: true,
        disableDefaultUI: true,
        center: new google.maps.LatLng(mainLocationLat, mainLocationLng),
      };



      var map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
      var mainLocationMarker = new google.maps.Marker(
        {
          position: mapOptions.center,
          map: map,
          animation: 'bounce',
        }
      );
      
      var eveningLocationMarker = new google.maps.Marker(
        {
          position: new google.maps.LatLng(eveningLocationLat, eveningLocationLng),
          map: map,
          animation: 'bounce',
        }
      );
    }
  };

})(jQuery);

function mapsInit() {

}
