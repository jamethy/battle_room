import * as React from "react";

export interface PopupButtonProps {
    label: string,
    onClick: React.MouseEventHandler,
    style?: React.CSSProperties,
}

export class PopupButton extends React.Component<PopupButtonProps, {}> {
    render() {
        const {label, onClick, style} = this.props;

        return (
            <button className="popupButton" style={style} onClick={onClick}>{label}</button>
        );
    }
}
