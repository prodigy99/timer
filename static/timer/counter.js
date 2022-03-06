self.onmessage = function (event){
    // console.log(event.data);
    let buffer = event.data;
    let arr = new Uint32Array(buffer);

    while(1){
        arr[0]++;
    }
}
