import * as React from "react";
import {PopupButton, PopupButtonProps} from "./PopupButton";

export interface PopupBoxProps {
    header: string,
    buttons: PopupButtonProps[],
    style?: React.CSSProperties,
}

const popupContainerStyle: React.CSSProperties = {
    width: "100vw",
    height: "100vh",
    display: "flex",
    justifyContent: "center",
    alignItems: "center"
};

const popupStyle: React.CSSProperties = {
    width: "15rem",
    padding: "1rem",
    background: "white",
    borderRadius: "1rem",
    backgroundColor: "grey",
};

const buttonContainerStyle: React.CSSProperties = {
    display: "flex",
    flexDirection: "column",
};

const headerStyle: React.CSSProperties = {
    textTransform: "uppercase",
};

export class PopupBox extends React.Component<PopupBoxProps, {}> {
    render() {
        const {style, header, buttons} = this.props;

        return <div style={popupContainerStyle}>
            <div style={{...popupStyle, ...(style || {})}}>
                <h1 style={headerStyle}>{header}</h1>
                <div style={buttonContainerStyle}>
                    {buttons.map(b => <PopupButton {...b}/>)}
                </div>
            </div>
        </div>
    }
}
