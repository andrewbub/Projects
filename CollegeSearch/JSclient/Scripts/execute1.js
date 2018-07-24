
var service = "http://student04.cse.nd.edu:51035/";
var college = "colleges/";
var sat = "sat/";
var act = "act/";
var siz = "pop/";
var tui = "cost/";
var city = "city/";
var region = "regions/";
var state = "states/";
school_list = [];
all_names =[];

list = [];
listsizes =[];
dict = {};

intsize = 0;
intcost = 0;
intstate = 0;
intcity = 0;
intregion = 0;
intact = 0;
intsat = 0; 

object = {  names : null,
            regions : null,
            sat : null,
            act : null,
            city : null,
            state : null,
            cost : null,
            size : null,
}

//xmlHTTP variables
xhrsize = new XMLHttpRequest();
xhrschool = new XMLHttpRequest();
xhrs = new XMLHttpRequest();
xhrregion = new XMLHttpRequest();
xhrsat = new XMLHttpRequest();
xhract = new XMLHttpRequest();
xhrcity = new XMLHttpRequest();
xhrstate = new XMLHttpRequest();
xhrcost = new XMLHttpRequest();
xhr =new XMLHttpRequest();

//lists that contain the results of the requests
satlist = [];
actlist = []; 
citylist = [];
regionlist = [];
sizelist = [];
costlist = [];
statelist = [];
/*-----------------------------General Functions-------------------------------------- */
function reset(){
    location.reload();
}

function getvalue( id){
    var x = document.getElementById(id)
    for (var i = 0; i < x.length; i++){
        var r = x[i];
        if(r.checked) return r.value
        else return null
    }

    return 'Error'
}

function inArray(needle,haystack){
    var count=haystack.length;
    for(var i=0;i<count;i++)
    {
        if(haystack[i]==needle){return false;}
    }
    return false;
}

function showresults(){
	var resultsDiv = new DIV();
	resultsDiv.createDiv('resultsDiv');
	resultsDiv.addtoDocument();

	var Results = new Label();
	Results.createLabel('Results', 'Results');
	Results.addtodiv('resultsDiv');

	console.log(school_list['0'])
	for(i = 0; i < school_list.length; i++){
		console.log(school_list[i])
		
		xhrschool.open("GET", service+college+school_list[i], false);
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
	var button = new Button();
	button.createButton('Search Again', 'Return');
    button.addtodiv('buttonDiv');
    button.addClickEventHandler(reset,school_list)
}

function fsubmit(){

    
    var x = document.getElementById("inputschool").value;
    xhrs.open("GET", service+college+x, false);
    xhrs.onload = function(e){
        var responsetext = xhrs.responseText;
        var responseinfo = JSON.parse(responsetext);
        school_name = responseinfo["Name"]
	if (school_name == "error") {
		alert("error: college not found")
	}
	else {
		school_list.push(school_name)
        	console.log(school_list)
		showresults()
        	return responseinfo;
	}
    }
    xhrs.onerror = function(e){
        console.log("fsubmit function failed");
    }

     xhrs.send(null)

}

/*----------------------------------------------------------------------------------- */
function get_names(object){
    xhr.open("GET",service+"names/",false);
    xhr.onload = function(e){
        console.log("in get names onload");
        var responsetext = xhr.responseText;
        var responseinfo = JSON.parse(responsetext);
        object.names = responseinfo["college"]
        console.log(responseinfo)
    }
    xhr.onerror = function(e){
        console.log("get names request failed");
    }
    xhr.send(null);
}

function getregion(object){
    var r = document.getElementById("option1").value;
    if (r != 'null'){
        
        xhrregion.open("GET", service+region+r, false);
        xhrregion.onload = function(e){
            console.log("region onload reached")
            var responsetext = xhrregion.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.regions = responseinfo["college"];
        }
        xhrregion.onerror = function(e){
            console.log("getregion function failed")
        }
        xhrregion.send(null)
    }
    if (r == 'null'){
        return null;
    }
}

function getsat(object){
    var s = document.getElementById("option2").value;
   
    if (s != 'null'){
       
        xhrsat.open("GET", service+sat+s, false);
        xhrsat.onload = function(e){
            console.log("sat onload reached")
            var responsetext = xhrsat.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.sat=responseinfo["college"];
        }
        xhrsat.onerror = function(e){
            console.log("getsat function failed")
        }
        xhrsat.send(null)
    }

    if (s == 'null'){
        return null;
    }
    
}

function getact(object){
    var a = document.getElementById("option3").value;
    if (a != 'null'){
        xhract.open("GET", service+act+a, false);
        xhract.onload = function(e){
            console.log("act onload reached")
            var responsetext = xhract.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.act =responseinfo["college"];
        }
        xhract.onerror = function(e){
            console.log("getact function failed")
        }
        xhract.send(null)
    }

    if (a == 'null'){
        return null;
    }
    
}

function getcity(object){
    var c = document.getElementById("option4").value;
    if (c != 'null'){
        xhrcity.open("GET", service+city+c, false);
        xhrcity.onload = function(e){
            console.log("city onload reached")
            var responsetext = xhrcity.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.city = responseinfo["college"];
        }
        xhrcity.onerror = function(e){
            console.log("getcity function failed")
        }
        xhrcity.send(null)
    }

    if (c == 'null'){
        return null;
    }
    
}

function getstate(object){
    var st = document.getElementById("option5").value;
    if (st != 'null'){
        
        xhrstate.open("GET", service+state+st, false);
        xhrstate.onload = function(e){
            console.log("city onload reached")
            var responsetext = xhrstate.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.state=responseinfo["college"];
        }
        xhrstate.onerror = function(e){
            console.log("getstate function failed")
        }
        xhrstate.send(null)
    }

    if (st == 'null'){
        return null;
    }
}

function getcost(object){
    var cost = getvalue("option7");
   
    if (cost != null){
        
        xhrcost.open("GET", service+tui+cost, false);
        xhrcost.onload = function(e){
            console.log("cost onload reached")
            var responsetext = xhrcost.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.cost = responseinfo["college"];
        }
        xhrcost.onerror = function(e){
            console.log("getcost function failed")
        }
        xhrcost.send(null)
    }

    if (cost == 'null'){
        return null;
    }
}

function getsize(object){
    var size = getvalue("option6")
    if (size != null){
        xhrsize.open("GET", service+siz+size, false);
        xhrsize.onload = function(e){
            console.log("size onload reached")
            var responsetext = xhrsize.responseText;
            var responseinfo = JSON.parse(responsetext);
            object.size = responseinfo["college"];
        }
        xhrsize.onerror = function(e){
            console.log("getcost function failed")
        }
        xhrsize.send(null)
    }
    if (size == 'null'){
        return null;
    }
}

function getall(object){



    if (object.size != null){ 
        sizelist = object.size;
        intsize = object.size.size();
        dict.intsize = sizelist;
        listsizes.push(intsize);
        list.push(sizelist);
    }
     
    if (object.cost != null){
        costlist = object.cost;
        intcost = object.cost.size();
        dict.intcost = costlist;
        listsizes.push(intcost);
        list.push(costlist);
    }

    if (object.state != null){
        statelist = object.state
        intstate = object.state.size();
        dict.intstate = statelist;
        listsizes.push(intstate);
        list.push(statelist);
    }

    if (object.city != null){
        citylist = object.city
        intcity = object.city.length;
        dict[intcity] = object.city;
        listsizes.push(intcity);
        list.push(citylist);
    }
    
    if (object.regions != null){
        regionlist = object.regions;
        intregion = object.regions.length;
        dict[intregion] = regionlist;
        listsizes.push(intregion);
        list.push(regionlist);
    }

    if (object.act != null){
        actlist = object.act;
        intact = object.act.size();
        dict.intact = actlist;
        listsizes.push(intact);
        list.push(actlist)
    }

    if (object.sat != null){
        satlist = object.sat;
        intsat = satlist.size();
        dict.intsat = satlist;
        listsizes.push(intsat);
        list.push(satlist);
    }
    // error testing console logs
    console.log(dict)
    console.log(object)
    console.log(list)

    //getting the smallest list to iterate over 
    var least = Math.min.apply(null, listsizes);
    console.log(least)
    var leastlist = dict[least]

    for (var x=0; x<leastlist.length; x++){
        for ( var y in dict){
            if( inArray(leastlist[x],dict[y]) ){
                continue;
            }
            else {
                leastlist.splice(x, 1);
            }
        }
    }

    for (var x=0; x,leastlist.length; x++){
        console.log(leastlist[x])
        school_list.push(leastlist[x]);
    }

    showresults();

}