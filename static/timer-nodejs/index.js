const { isMainThread, Worker, parentPort } = require('worker_threads');

let buffer = new SharedArrayBuffer(16);


if (isMainThread) {
    let buffer = new SharedArrayBuffer(16);
    const worker = new Worker(__filename);
    worker.postMessage(buffer)
    let t0 = performance.now();
    setTimeout(() => {
        let arr = new Uint32Array(buffer);

        let elapsed = performance.now() - t0;
        console.log("Elapsed Time: " + elapsed);

        let count = arr[0];
        console.log("Counter: " + count);
        let precision = elapsed / count;
        console.log("Precision: " + precision + " ms");
    }, 1000);
} else {
    parentPort.on("message", (buffer) => {
        let arr = new Uint32Array(buffer);
        while (true) {
            arr[0]++;
        }
    })
}