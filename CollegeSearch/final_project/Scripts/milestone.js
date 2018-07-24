// written by: Andrew Bub, Harry Gebremedhin, Molly Pierce 
//general functions like addtodocument
function Item(){
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }
};

// function for dropdown related stuff
function Dropdown(){
    this.createDropdown = function(dict, name, id, selected){
        this.item = document.createElement("select")
		this.name = name

		var ttmp = document.createElement("label")
		ttmp.setAttribute("name", name)			
		ttmp.innerHTML = this.name
		this.item.appendChild(ttmp)

       		for(var x in dict){
            		var tmp =document.createElement("option")
            		tmp.setAttribute('value',dict[x])
            		tmp.innerHTML= x + '<br>' 
           
            		this.item.appendChild(tmp)
        	}

    },
  
    this.getSelected = function(){
        this.item=document.getElementById()
    },

    this.addToDocument = function(){
        document.body.appendChild(this.item);

    }
};

//function for creating divs
function DIV(){
    this.createDiv=function(id){
        this.item=document.createElement('div');
        this.item.setAttribute('id', id);
    }
    this.addtodiv=function(id){
        document.getElementById(id).appendChild(this.item);
    }
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }
};


// function to create buttons
function Button (){
    this.createButton = function(text,id){
        this.item=document.createElement('button');
        this.item.setAttribute("id",id);
        this.item.setAttribute("name",text);
        this.item.innerHTML=text;
    },

    this.addClickEventHandler = function(handler,input){
        this.item.onmouseup=function(){
            handler(input);
        }

    }
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }
    this.addtodiv=function(id){
        document.getElementById(id).appendChild(this.item);
    }
};

// function to add the texts 
function Label(){
    this.createLabel =function(text,id){
        this.item=document.createElement('p');
        this.item.setAttribute("id",id);
        var textLabel = document.createTextNode(text); 
        this.item.appendChild(textLabel);
    
    },

    this.setText = function(text){
        this.item.innerHTML=text;

    }
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }
    this.addtodiv=function(id){
        document.getElementById(id).appendChild(this.item);
    }
};
//
// function to add URLs
function Hyperlink(){
	this.createHyperlink =function(url, name, id){
		this.item =document.createElement('a');
		//this.item.setAttribute("href", url);
		var linkText = document.createTextNode(name);
		this.item.appendChild(linkText);
		this.item.title = name;
		this.item.href = 'http://' + url;
		console.log(this.item);
		document.body.appendChild(this.item);

    }
    this.addtodiv=function(id){
        document.getElementById(id).appendChild(this.item);
    }
};

// Functions for Raido buttons 
function Radio(){
    this.createRadio = function(name, labels, id){
        this.item = document.createElement("form") //bc in HTML: <form action="">...</form>
		this.name = name

		// add title label
		var ttmp = document.createElement("label")
		ttmp.setAttribute("name", name)			
		ttmp.innerHTML = this.name + '<br>'
		this.item.appendChild(ttmp)

		for (var x in labels) //x is the index of whatever labels is
		{
			var lx = labels[x]
			//console.log('x is ' + x + ' and labels[x] is ' + lx)
			var tmp = document.createElement("input")
			tmp.setAttribute("type","radio")
			tmp.setAttribute("name", name) //choice
			tmp.setAttribute("value", lx) //alpha, beta, oatmeal

			//adding labels
			var ltmp = document.createElement("label")
			ltmp.setAttribute("id", id+"_label_"+x) //theRadioButton_label_#
			ltmp.innerHTML = labels[x] + '<br>'

			this.item.appendChild(tmp)
		    this.item.appendChild(ltmp)
        }
    },  

    this.getValue = function() {
        var radios = this.item.elements[this.name]
        for (var i = 0; i < radios.length; i++){
            var r = radios[i]
            if(r.checked) return r.value
        }
        
        return 'error'
    }
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }

};

function textbox(){
    this.createtextbox = function(name,enames,labels,id){
        this.item = document.createElement("form")
        this.name = name
        for (var x in labels){
            var lx = labels[x]
            var tmp = document.createElement("input")
            tmp.setAttribute("type","text")
            tmp.setAttribute("name",labels[x])
            

            // Label realted things
            var ltmp = document.createElement("label")
            ltmp.setAttribute("id", id+"_label_"+x) // ids can come up with something else 
            ltmp.innerHTML = enames[x]
            
            this.item.appendChild(ltmp)
            this.item.appendChild(tmp)
        }

    },

    this.getValue = function() { // function returns null if no input but returns string if input present 
       if (this.item.value != null){
           return this.item.value
       }
       return null
    }
    this.addtoDocument =function(){
        document.body.appendChild(this.item);
    }

};
