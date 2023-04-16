import { Socket, createSocket } from 'node:dgram';
import EventEmitter from 'node:events';
import { fromBuffer, ArgumentType, toBuffer } from 'osc-min';

const port = 57123;
const host = '127.0.0.1';

const log = console.log;

let client: Socket;
// export const eventClient = new EventEmitter();

function getClient() {
    if (!client) {
        client = createSocket({
            type: 'udp4',
            reuseAddr: true,
        });

        client.on('error', (err) => {
            log(`client error:\n`, err);
            client.close();
        });

        client.on('message', (msg: Buffer) => {
            const decoded = fromBuffer(msg);
            // eventClient.emit(decoded.address, decoded.args);
            // if (decoded.address === '/done') {
            //     eventClient.emit(`/done${decoded.args[0].value}`, decoded.args);
            // }

            console.log('#####', decoded);


            // log('Client msg:', msg.toString(), decoded);
            if (decoded.address === '/fail') {
                console.error('SC Error:', decoded)
            }
        });
    }
    return client;
}

export function send(address: string, ...args: ArgumentType[]) {
    const client = getClient();
    // log('Send:', address, args);
    const buffer = toBuffer({
        address,
        args,
    });

    // console.log('#####', buffer.toString());

    return new Promise<void>((resolve, reject) => {
        client.send(buffer, 0, buffer.length, port, host, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve();
            }
        });
    });
}

export function int(value: number) {
    return {
        type: "integer",
        value
    };
}

export async function init() {
    await send('/msg', int(1), int(0), '/synth', 'hello', int(123), 0.2);
    await send('/msg_get', int(1));
    await send('/sub');
}
