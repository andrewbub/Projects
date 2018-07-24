// Harry Gebremedhin, Andrew Bub, Molly Pierce
// written with the inspiration of The Father, The son and The holy spirit lol

var service = "http://student04.cse.nd.edu:51035/";

var college = "colleges/";

school_list = [];

var xhrschool = new XMLHttpRequest();

object = {  regions : null,
            sat : null,
            act : null,
            city : null,
            state : null,
            cost : null,
            size : null,
            response: [],
}

/*-----------------------------General Functions-------------------------------------- */

function reset(object){
    object.regions = null;
    object.sat = null;
    object.act = null;
    object.city = null;
    object.state = null;
    object.cost = null;
    object.size = null;
    object.response = [];

    location.reload();
   
    xhrr = new XMLHttpRequest();
    xhrr.open("PUT", service+"reset/",false);
    xhrr.onload = function(e){

    }
    xhrr.onerror = function(e){
        console.log("reset request failed");
    }
    
    xhrr.send(null);

}

function getvalue(id){
    var x = document.getElementById(id)
    for (var i = 0; i < x.length; i++){
        var r = x[i];
        if(r.checked) return r.value
        else return null
    }

    return 'Error'
}

function showresults(object){
	var resultsDiv = new DIV();
	resultsDiv.createDiv('resultsDiv');
	resultsDiv.addtoDocument();

	var Results = new Label();
	Results.createLabel('Results', 'Results');
	Results.addtodiv('resultsDiv');

	//console.log(school_list['0'])
	for(i = 0; i < object.response.length; i++){
		console.log(object.response[i])
		
		xhrschool.open("GET", service+college+object.response[i], false);
		xhrschool.onload = function(e) {
			Item();
			Button();
			Hyperlink();
			Label();
			DIV();
			Button.prototype = Item();
			Label.prototype = Item();
			Hyperlink.prototype = Item();
			DIV.prototype = Item();

			var responsetext = xhrschool.responseText;
			var responseinfo = JSON.parse(responsetext);
		
			    var name = responseinfo["Name"];
       			var city = responseinfo["City"];
        		var state = responseinfo["State"];
        		var website = responseinfo["WebURL"];
        		var cost = responseinfo["Cost"];
        		var fin = responseinfo["FinURL"];
		
			// creating the different divs
                var schoolDiv= new DIV();
                schoolDiv.createDiv('schoolDiv' + i); 
                schoolDiv.addtoDocument();
                if (i%4 == 0 || i==0){
                    document.getElementById('schoolDiv'+i).setAttribute("style","clear: both; margin-left: 7%; margin-top: 3%; float: left; position: relative; background-color: #ffffff; border: 1px solid black; width: 20%; height: 45%; text-align: center;")
                } else {
                    document.getElementById('schoolDiv' + i).setAttribute("style", "float: left; position: relative; margin-left: 2%; margin-top: 3%; background-color: #ffffff; border: 1px solid black; width: 20%; height: 45%; text-align: center;")
                }
        		// School Division - dynamically create in for loop
        		var Name = new Label();
       			Name.createLabel(name,'Name');
			    Name.addtodiv('schoolDiv' + i);

       			var Location = new Label();
       			Location.createLabel(city + ', ' + state,'Location');
       		    	Location.addtodiv('schoolDiv' + i); 
	
	       		var Website = new Hyperlink();
       			Website.createHyperlink(website,'Website', 'website');
       			Website.addtodiv('schoolDiv' + i);

       			var Cost = new Label();
       			Cost.createLabel('Tuition: $' + cost,'Cost');
       			Cost.addtodiv('schoolDiv' + i);

       			var Fin = new Hyperlink();
       			Fin.createHyperlink(fin,'Financial Aid', 'fin');
       			Fin.addtodiv('schoolDiv' + i);

			return responseinfo;
		}

		xhrschool.onerror = function(e) {
			console.log("resultspage function failed")
		}


		xhrschool.send(null)

	}

	var buttonDiv= new DIV();
	buttonDiv.createDiv('buttonDiv');
	buttonDiv.addtoDocument();

    // Button Division
    var blank = new Label();
    blank.createLabel(' ','Blank');
    blank.addtodiv('buttonDiv');

	var button = new Button();
	button.createButton('Search Again', 'Return');
    button.addtodiv('buttonDiv');
    button.addClickEventHandler(reset,object)
}

function fsubmit(){
    var x = document.getElementById("inputschool").value;
    var xhrs = new XMLHttpRequest();
    xhrs.open("GET", service+college+x, false);
    xhrs.onload = function(e){
        var responsetext = xhrs.responseText;
        var responseinfo = JSON.parse(responsetext);
        school_name = responseinfo["Name"]
	if (school_name == "error") {
		alert("error: college not found")
	}
	else {
		object.response.push(school_name)
        console.log(object.response)
		showresults(object)
        	//return responseinfo;
	}
    }
    xhrs.onerror = function(e){
        console.log("fsubmit function failed");
    }

     xhrs.send(null)

}

function getall(object){
    
    var size = getvalue("option6")
    var cost = getvalue("option7")
    var city = document.getElementById("option4").value;
    var act = document.getElementById("option3").value;
    var sat = document.getElementById("option2").value;
    var regions = document.getElementById("option1").value;
    var state = document.getElementById("option5").value;
   
    object.size = size;
    object.cost = cost;
    object.city = city;
    object.regions = regions;
    object.sat = sat;
    object.act = act;
    object.state = state;
    object.response = [];

    var xhr = new XMLHttpRequest();
    xhr.open("PUT", service+"results/",false);
    xhr.onload = function(e){
        var response = xhr.responseText
        var responseinfo = JSON.parse(response)
        //console.log(responseinfo)
        object.response = responseinfo["colleges"]
        console.log(object.response)
        showresults(object);
    }
    xhr.onerror = function(e){
        console.log("Put request to resulsts resource failed");
    }
    var data = JSON.stringify(object);
    xhr.send(data);

}
