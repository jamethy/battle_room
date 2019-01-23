import * as React from "react";
import {PopupBox, PopupBoxProps} from "./PopupBox";

export interface MainProps {
}

enum MainPage {
    Home,
    SinglePlayer,
    HostOnline,
    JoinOnline,
    Settings,
}

interface MainState {
    currentPage: MainPage,
}

const popupStyle: React.CSSProperties = {
    backgroundColor: "grey"
};

export class Main extends React.Component<MainProps, MainState> {

    private readonly pages : Map<MainPage, PopupBoxProps>;

    constructor(props: MainProps) {
        super(props);

        this.state = {
            currentPage: MainPage.Home,
        };

        this.navigateTo = this.navigateTo.bind(this);

        this.pages = new Map<MainPage, PopupBoxProps>();
        this.pages.set(MainPage.Home, {
            header: "BATTLE ROOM",
            style: popupStyle,
            buttons: [
                {
                    label: "Single Player",
                    onClick: () => this.navigateTo(MainPage.SinglePlayer),
                },
                {
                    label: "Host Online",
                    onClick: () => this.navigateTo(MainPage.HostOnline),
                },
                {
                    label: "Join Online",
                    onClick: () => this.navigateTo(MainPage.JoinOnline),
                },
                {
                    label: "Settings",
                    onClick: () => this.navigateTo(MainPage.Settings),
                },
                {
                    label: "Quit",
                    onClick: () => this.navigateTo(MainPage.Home),
                },
            ]
        });
        this.pages.set(MainPage.SinglePlayer, {
            header: "SINGLE PLAYER",
            style: popupStyle,
            buttons: [
                {
                    label: "Play",
                    onClick: () => this.navigateTo(MainPage.SinglePlayer),
                },
                {
                    label: "Back",
                    onClick: () => this.navigateTo(MainPage.Home),
                },
            ]
        });
    }

    navigateTo(page: MainPage) {
        this.setState({currentPage: page});
    }

    render() {
        const currentPageProps = this.pages.get(this.state.currentPage);
        return <PopupBox {...currentPageProps} />
    }
}
