import * as React from "react";

export interface ChargeBarProps {
    charge: number, // 0 - 1
    width: number, // in pixels
    type: "GunCharge" | "JumpCharge",
}

export class ChargeBar extends React.Component<ChargeBarProps, {}> {

    render() {
        const {charge, width, type} = this.props;
        let limitedCharge = Math.min(1, Math.max(0, charge));
        let height = width / 15;

        const barStyle: React.CSSProperties = {
            background: type === 'GunCharge' ? 'red' : 'green',
            height: height + 'px',
            width: (width * limitedCharge) + 'px',
        };

        return (
            <div style={barStyle}/>
        );
    }
}
