interface CefQuery {
    request: string,
    persistent: boolean,
    onSuccess: (response: string) => void,
    onFailure: (error_code: number, error_message: string) => void,
}

interface Request {
    method: string,
    route: string,
    body?: Object,
}

function appCall(request: Request,
                 onSuccess: (response: string) => void,
                 onFailure: (error_code: number, error_message: string) => void) {
    // @ts-ignore
    window.cefQuery({
        request: JSON.stringify({
            method: request.method,
            route: request.route,
            body: JSON.stringify(request.body),
        }),
        persistent: false,
        onSuccess,
        onFailure,
    });
}

function logSuccess(response: string) {
    console.log(`Success response: ${response}.`);
}

function logFailure(error_code: number, error_message: string) {
    console.error(`Failure response: {${error_code}, ${error_message}}`);
}

export function quitGame() {
    appCall(
        {
            method: "POST",
            route: "/quit",
        },
        logSuccess,
        logFailure
    );
}


// Window: mainWindow
//     Width: 1500
//     Height: 1000
//
// Interface: Game
//     Window: mainWindow
//     Layer: 10
//     Camera: Pyramid

export function testAppCall() {
    appCall(
        {
            method: "POST",
            route: "/test",
            body: {
                window: {
                    value: "secondWindow",
                    width: 1000,
                    height: 1000,
                },
                interface: {
                    value: "game",
                    window: "secondWindow",
                    layer: 10,
                    camera: "pyramid"
                }
            }
        },
        logSuccess,
        logFailure,
    )
}
