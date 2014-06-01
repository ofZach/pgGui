
var ofPath = "../";
var addons = (1,2);
var addonList = new Object();
var platformList = new Array();


$(document).ready(function() {

     var data = {
          "platforms": {
            "osx": {
                "available" : "true",
                "default" : "true",
                "selected" : "true"
            },
            "windowCB": {
                "available" : "false",
                "default" : "false",
                "selected" : "false"
            },
            "windowsVS": {
                "available" : "false",
                "default" : "false",
                "selected" : "false"
            }
          }
        }


     var removeIcon = "<span class='glyphicon glyphicon-remove' style='float:right'></span>"
                  
     addonList["c"] = false;
     addonList["a"] = true;
     addonList["b"] = false;
     addonList["d"] = true;
     addonList["e"] = false;
     
    for (var i in data.platforms) {
          //alert(platform["name"]);
          //alert(i);
          var platform = data.platforms[i];
          platform["name"] = i;
          platformList.push(platform);
    }


     $('#configPage').hide();
     $('#addonPage').hide();

     refreshChosenAddons();
     refreshPlatformsList();
    // $('.btn').click(function() {
    //     window.app.ChangeTextInJS('Hello World!');
    // });

    $('#configBtn').click(function() {
    	$('#mainPage').hide(); //attr("style", "background-color:#ff0099;")
        $('#configPage').show();
         $('#addonPage').hide();
    });

     $('#addonBtn').click(function() {
    	$('#mainPage').hide(); //attr("style", "background-color:#ff0099;")
    	refreshAddonsList();
        $('#addonPage').show();
    });

     $('#backBtn').click(function() {
     	refreshChosenAddons();
    	$('#mainPage').show(); //attr("style", "background-color:#ff0099;")
        $('#configPage').hide();
        $('#addonPage').hide();
        
    });

     $('#backBtn2').click(function() {
     	refreshChosenAddons();
    	$('#mainPage').show(); //attr("style", "background-color:#ff0099;")
        $('#configPage').hide();
        $('#addonPage').hide();

    });


    function refreshChosenAddons(){


    	$("#chosenAddonList").empty();
    	for (var key in addonList) {
	 			if (Boolean(addonList[key]) == true){
    			str= "<div>" + key + "," + addonList[key] + "</div>";
	 			$(str).appendTo("#chosenAddonList");
	 		}
	 		
    	}
    }


    function refreshPlatformsList(){

        $("#platformList").empty();
        for (var i = 0; i <platformList.length; i++) {

            var availableStr = "";
            var selectedStr = "";

            if ((platformList[i]["available"]) == "false"){
                availableStr = " unavailable ";
            }

            if ((platformList[i]["selected"]) == "true"){
                selectedStr = " selected ";
            }

            var startDiv = "<div class='platform ";
            startDiv += availableStr;
            startDiv += selectedStr;
            startDiv += "'>";

            if ((platformList[i]["selected"]) == "true"){
                str= startDiv + platformList[i]["name"] +  removeIcon + "</div>";
                $(str).appendTo("#platformList");
            } else {
                str= startDiv + platformList[i]["name"] +  "</div>";
                $(str).appendTo("#platformList");
            }
        }

    }
                  
            

    function refreshAddonsList(){
    	$("#selectAddonList").empty();
                  
    
                  
                  
    	for (var key in addonList) {
             if (Boolean(addonList[key]) == true){
                    str= "<div class='addonListing selected' id='" + key +  "'>" + key + removeIcon + "</div>";
                    $(str).appendTo("#selectAddonList");
            } else {
                  str= "<div class='addonListing' id='" + key + "'>" + key + removeIcon + "</div>";
                  
                  $(str).appendTo("#selectAddonList");
            }
    	}

    	$('.addonListing').click(function() {
    		if ($(this).hasClass('selected')){
    			var id = $(this).attr("id");
    			addonList[id]= false;
				$(this).removeClass('selected');
    		} else {
    			var id = $(this).attr("id");
    			addonList[id]= true;

    			$(this).addClass('selected');
    		}
    	});
    }

                  
    window.app.TellMeSomething();
                  
    $('#projName').html(ofPath);
                  
    
});

function ChangeText(text) {
    $('#text').html(text);
}


//.toggleClass()  looks useful for toggles...
