export type AppCallSuccessFunction = (response: string) => void;
export type AppCallFailureFunction = (error_code: number, error_message: string) => void;

interface Request {
    method: string;
    route: string;
    body?: Object;
}

interface WorldUpdater {
    type: "Server";
    user: string;
    resource?: string;
}

interface Interface {
    type: "Game" | "Menu";
    window: string;
    layer?: number;
    url?: string;
    camera?: "Pyramid";
}

interface Resource {
    worldUpdater?: WorldUpdater;
    interfaces?: Interface[];
}

let appCall = function (request: Request,
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
};

// overwrite appCall function if cefQuery does not exist (testing in browser)
// @ts-ignore
if (!window.cefQuery) {
    appCall = function (request: Request,
                        onSuccess: AppCallSuccessFunction,
                        onFailure: AppCallFailureFunction) {
        console.log({
            method: request.method,
            route: request.route,
            body: request.body,
        });
    }
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

export function closeMenu() {
    appCall(
        {method: "POST", route: "/close"},
        logSuccess,
        logFailure
    );
}

export function postResource(resource: Resource) {
    appCall(
        {method: "POST", route: "/message", body: resource},
        logSuccess,
        logFailure
    );
}

export function putResource(resource: Resource) {
    appCall(
        {method: "PUT", route: "/message", body: resource},
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
