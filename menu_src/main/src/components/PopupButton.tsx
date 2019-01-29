import * as React from "react";

export interface PopupButtonProps {
    label: string,
    onClick: React.MouseEventHandler,
    style?: React.CSSProperties,
}

const popupButtonStyle: React.CSSProperties = {
    background: "none",
    boxShadow: "none",
    fontSize: "2rem",
    height: "4rem",
    marginTop: "0.25rem",
    marginBottom: "0.25rem",
    border: "0.25rem solid #2b2b2b",
    borderRadius: "0.5rem",
};

export class PopupButton extends React.Component<PopupButtonProps, {}> {
    render() {
        const {label, onClick, style} = this.props;

        return (
            <button style={{...popupButtonStyle, ...style}} onClick={onClick}>{label}</button>
        );
    }
}
