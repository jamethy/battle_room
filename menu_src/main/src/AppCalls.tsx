export type AppCallSuccessFunction = (response: string) => void;
export type AppCallFailureFunction = (error_code: number, error_message: string) => void;

interface Request {
    method: string;
    route: string;
    body?: Object;
}

function appCall(request: Request,
                 onSuccess: AppCallSuccessFunction,
                 onFailure: AppCallFailureFunction) {
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

let logSuccess: AppCallSuccessFunction = function (response: string): void {
    console.log(`Success response: ${response}.`);
};

let logFailure: AppCallFailureFunction = function (error_code: number, error_message: string): void {
    console.error(`Failure response: {${error_code}, ${error_message}}`);
};

export function quitGame() {
    appCall(
        {method: "POST", route: "/quit"},
        logSuccess,
        logFailure
    );
}

export function getApplicationState(onSuccess: AppCallSuccessFunction) {
    appCall(
        {method: "GET", route: "/application"},
        onSuccess,
        logFailure,
    )
}
