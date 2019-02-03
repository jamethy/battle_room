import {PlayerSelectProps} from "./components/PlayerSelect";

export type AppCallSuccessFunction = (response: string) => void;
export type AppCallFailureFunction = (error_code: number, error_message: string) => void;

interface Request {
    method: string;
    route: string;
    body?: Object;
}

interface Resource {
    key: string;
    value?: string | number | boolean;
    subs?: Resource[];
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

export interface GameElement {
    type: 'PlayerSelect',
    props: PlayerSelectProps,
}

export function getGameElements(onSuccess: (elements: GameElement[]) => void) {
    appCall(
        {method: "GET", route: "/game-elements"},
        (response) => onSuccess(JSON.parse(response)),
        logFailure,
    )
}
