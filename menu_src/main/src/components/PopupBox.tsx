import * as React from "react";
import {PopupButton, PopupButtonProps} from "./PopupButton";

export interface PopupBoxProps {
    style: React.CSSProperties,
    header: string,
    buttons: PopupButtonProps[],
}

const buttonContainerStyle: React.CSSProperties = {
    display: "flex",
    flexDirection: "column",
};

export class PopupBox extends React.Component<PopupBoxProps, {}> {
    render() {
        const {style, header, buttons} = this.props;

        return <div className="popupContainer">
            <div style={style}>
                <h1>{header}</h1>
                <div style={buttonContainerStyle}>
                    {buttons.map(b => <PopupButton {...b}/>)}
                </div>
            </div>
        </div>
    }
}
