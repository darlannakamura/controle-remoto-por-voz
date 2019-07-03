var childProcess = require("child_process");
var spawn = childProcess.spawn;
// var oldSpawn = childProcess.spawn;
// function mySpawn() {
//     console.log('spawn called');
//     console.log(arguments);
//     var result = oldSpawn.apply(this, arguments);
//     return result;
// }
// childProcess.spawn = mySpawn;

// run arp -a
var arp = async (operationalSystem) => {
    const option = (operationalSystem == 'windows') ? "-a" : "-n";

    const arp = spawn("arp", [option]);
    
    var buffer = '';
    var error = '';

    arp.stdout.on('data', (data) => {
        buffer += data;
    });

    arp.stderr.on('data', (data) => {
        error += data;
    });

    arp.on('close', (code) => {
        if(code !== 0){
            console.log(`Error running arp -a. CODE ${code}: ${error}`);
            return;
        }

        const  table = buffer.split('\r\n');


        var arpArray = [];

        for (lineIndex = 3; lineIndex < table.length; lineIndex++) {

            //parse this format
            //[blankline]
            //Interface: 192.º68.1.54
            //  Internet Address      Physical Address     Type
            //  192.168.1.1           50-67-f0-8c-7a-3f    dynamic

            
            
            var parts = table[lineIndex].split(' ').filter(String);

            // console.log('parts');
            // console.log(parts);
            if(parts.length != 0 && parts[2].includes('din')){
                arpArray.push({
                    ip: parts[0],
                    mac: parts[1].replace(/-/g, ':'),
                    type: parts[2]
                });
            }
        }
        
        console.log(arpArray);
        return arpArray;

        // console.log(`Can't finded the arp table.`);
        // return;
    });

}

var ipNodeMcu =  async() => {
    const macNodeMCU = '84-0d-8e-84-29-ee';
    const arp = arp('windows');

    const ip = '';

    arp.forEach( (e) => {
        if (e.mac == macNodeMCU){
            ip = e.ip;
        }
    });

    return ip;
};

try{
    // console.log(getMacOnWindows().then( res => console.log(res)));
    // arp('windows');
    ipNodeMcu();
} catch (e) {
    console.log(e);
}

// const enderecoMacDoNodeMCU = '84-0d-8e-84-29-ee';