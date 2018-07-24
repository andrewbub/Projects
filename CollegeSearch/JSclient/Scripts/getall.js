function getall(){

    var list = [];
    var listsizes =[];
    var dict = {};

    var size = getsize();
    if (size != null){
    var sizelist = size["college"];
    var intsize = sizelist.size();
    dict[intsize] = sizelist;
    listsizes.push(intsize);
    list.push(sizelist);
    }

    var cost = getcost();
    if (cost != null){
    var costlist = cost["college"];
    var intcost = costlist.size();
    dict[intcost] = costlist;
    listsizes.push(intcost);
    list.push(costlist);
    }

    var state = getstate();
    if (state != null){
    var statelist = state["college"];
    var intstate = statelist.size();
    dict[intstate] = statelist;
    listsizes.push(intstate);
    list.push(statelist);
    }

    var city = getcity();
    if (city != null){
    var citylist = city["college"];
    var intcity = citylist.size();
    dict[intcity] = citylist;
    listsizes.push(intcity);
    list.push(citylist);
    }

    var region = getregion();
    if (region != null){
    var regionlist = region["college"]
    var intregion = regionlist.size()
    dict[intregion] = regionlist
    listsizes.push(intregion)
    list.push(regionlist)
    }

    var act = getact();
    if (act != null){
    var actlist = act["college"];
    var intact = actlist.size();
    dict[intact] = actlist
    listsizes.push(intact)
    list.push(actlist)
    }

    var sat = getsat();
    if (sat != null){
    var satlist = sat["college"];
    var intsat = satlist.size();
    dict[intsat] = satlist
    listsizes.push(intsat)
    list.push(satlist)
    }

    var least = Math.min.apply(Math, listsizes);
    var leastlist = dict[least]

    for (var x=0; x<leastlist.length; x++){
        for ( var y in dict){
            if( inarray(leastlist[x],dict[y]) ){
                continue;
            }

            else {
                leastlist.splice(x, 1);
            }
        }
    }

    for (var x=0; x,leastlist.length; x++){
        school_list.push(leastlist(x));
    }
    
    showresults();

}



/*


    console.log(list)
    console.log(dict)

   // var least = Math.min(intsize, intcost, intstate, intsat, intact, intcity, intregion);
    for (var key in dict){
        

    }
    console.log(least)
    var choice = dict[least];
    var resultlist=[];
    var location = list.indexOf(choice);
    list.splice(location,1);

    var listsize = list.length;
    var choicesize = choice.length;


    for (var y=0; y< choicesize; y++){
        if (list[y]){
            for (var x=0; x< listsize; x++){
                if ( inArray(choice[y],list[x]) ) {
                    resultlist.push(choice[x])
                }
            }
        }
        else y++
    }
    console.log(resultlist)
    return resultlist;
*/
