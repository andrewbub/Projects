function get_names(){
    xhr.open("GET",service+"names/",true);
    xhr.onload = function(e){
        console.log("in get names onload");
        var responsetext = xhr.responseText;
        var responseinfo = JSON.parse(responsetext);
        var listnames = responseinfo["college"];

        if (document.getElementById("option6") != 'null'){
            var s = document.getElementById("option6") != "null";
            xhrsize.open("Get",service+siz+s,true);
            xhrsize.onload(e,)

    }
    xhr.onerror = function(e){
        console.log("get names request failed");
    }
    xhr.send(null);
    
}