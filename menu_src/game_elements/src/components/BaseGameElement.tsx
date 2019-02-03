import * as React from "react";

export interface BaseGameElementProps {
    uniqueId: string;
    x: number;
    y: number;
}

export interface BaseGameElementState {
}


export class BaseGameElement<P extends BaseGameElementProps, T extends BaseGameElementState> extends React.Component<P, T> {
}
