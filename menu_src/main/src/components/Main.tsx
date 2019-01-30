import * as React from "react";
import {PopupBox, PopupBoxProps} from "./PopupBox";
import {closeMenu, postResource, quitGame} from "../AppCalls";

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

export class Main extends React.Component<MainProps, MainState> {

    private readonly pages: Map<MainPage, PopupBoxProps>;

    constructor(props: MainProps) {
        super(props);

        this.state = {
            currentPage: MainPage.Home,
        };

        this.navigateTo = this.navigateTo.bind(this);

        this.pages = new Map<MainPage, PopupBoxProps>();
        this.pages.set(MainPage.Home, {
            header: "Battle Room",
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
                    label: "Close",
                    onClick: closeMenu,
                },
                {
                    label: "Quit",
                    onClick: quitGame,
                },
            ]
        });
        this.pages.set(MainPage.SinglePlayer, {
            header: "Single Player",
            buttons: [
                {
                    label: "Play",
                    onClick: () => {
                        postResource({
                            key: "WorldUpdater",
                            value: "Server",
                            subs: [
                                {
                                    key: "Resource",
                                    value: "worlds/test_world",
                                },
                                {
                                    key: "User",
                                    value: "username",
                                }
                            ]
                        });
                        postResource({
                            key: "Interface",
                            value: "Game",
                            subs: [
                                {
                                    key: "Window",
                                    value: "mainWindow",
                                },
                                {
                                    key: "Layer",
                                    value: 10,
                                },
                                {
                                    key: "Camera",
                                    value: "Pyramid",
                                },
                            ]
                        });
                        closeMenu();
                    },
                },
                {
                    label: "Back",
                    onClick: () => this.navigateTo(MainPage.Home),
                },
            ]
        });
        this.pages.set(MainPage.Settings, {
            header: "Settings",
            buttons: [
                {
                    label: "Add screen",
                    onClick: () => {},
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
        let currentPage = this.state.currentPage;
        if (!this.pages.has(currentPage)) {
            console.error("Unknown page requested: " + currentPage + ". Going home.");
            currentPage = MainPage.Home;
        }
        const currentPageProps = this.pages.get(currentPage);
        return <PopupBox {...currentPageProps} />
    }
}
