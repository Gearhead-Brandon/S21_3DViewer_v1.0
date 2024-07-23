/*!
    @file
    @brief Header file describing the styles
*/
#ifndef STYLES_TABLES_HPP
#define STYLES_TABLES_HPP


#define FontStyle "font-family: Georgia;"


#define LabelStyle "color: black;"       \
                   "font: bold 15px;"     \


#define LoadButtonStyle "QPushButton {"                 \
                        "    color: white;"              \
                        "    background-color: #0d0502;"  \
                        "    font: bold 15px;"             \
                        "    height: 23px;"                 \
                        "}"                                  \
                                                              \
                        "QPushButton:hover {"                  \
                        "    background-color: #1f1d1d;"        \
                        "}"                                      \


#define TextEditStyle  "QTextEdit {"                       \
                            "background-color: #f0f0f0;"    \
                            "border: 2px solid #000000;"     \
                            "font: bold 13px;"                \
                            "border-top-left-radius: 10px; "   \
                            "border-top-right-radius: 10px;"    \
                        "}"                                      \


#define ScreenButtonStyle "QPushButton {"                   \
                            "    border-radius: 10px; "      \
                            "    color: white;"               \
                            "    background-color: #16191c;"   \
                            "    font: bold 16px;"              \
                            "    height: 26px;"                  \
                            "}"                                   \
                                                                   \
                            "QPushButton:hover {"                   \
                            "    background-color: #33383d;"         \
                          "}"                                         \


#define GifButtonStyle  "QPushButton {"                  \
                        "    border-radius: 10px; "       \
                        "    color: white;"                \
                        "    background-color: #33383d;"    \
                        "    font: bold 16px;"               \
                        "    height: 26px;"                   \
                        "}"                                    \
                                                                \
                        "QPushButton:hover {"                    \
                        "    background-color:  #16191c;"         \
                        "}"                                        \


#define MoveSliderStyle "QSlider::groove:horizontal {"    \
                        "    border-radius: 9px;       "   \
                        "    height: 7px;              "    \
                        "    margin: -1px 0;           "     \
                        "}"                                   \
                                                               \
                        "QSlider::handle:horizontal {"          \
                        "    background-color: white;"           \
                        "    border: 1px solid grey;"             \
                        "    height: 14px;     "                   \
                        "    width: 12px;"                          \
                        "    margin: -4px 0;"                        \
                        "    border-radius: 7px  ;"                   \
                        "    padding: -4px 0px;  "                     \
                        "}"                                             \
                                                                         \
                        "QSlider::add-page:horizontal {"                  \
                        "    background: #e9e9e9;"                         \
                        "    border: 1px solid grey;"                       \
                        "}"                                                  \
                                                                              \
                        "QSlider::sub-page:horizontal {"                       \
                        "    background: #5fbafa;"                              \
                        "    border: 1px solid grey;"                            \
                        "}"                                                       \


#define ValueStyle  "border: 1px solid black;"  \
                    "border-radius: 10px;"       \
                    "background: #202326 ;"       \
                    "color: white;"                \


#define IncreaseButtonStyle "QPushButton {"                  \
                            "    border-radius: 4px; "        \
                            "    color: white;"                \
                            "    background-color: #141110;"    \
                            "    font: bold 13px;"               \
                            "    height: 26px;"                   \
                            "}"                                    \
                                                                    \
                            "QPushButton:hover {"                    \
                            "    background-color: #302b29;"          \
                            "}"                                        \


#define DecreaseButtonStyle "QPushButton {"                 \
                            "    border-radius: 4px; "       \
                            "    color: white;"               \
                            "    background-color: #3d3735;"   \
                            "    font: bold 13px;"              \
                            "    height: 26px;"                  \
                            "}"                                   \
                                                                   \
                            "QPushButton:hover {"                   \
                            "    background-color: #141110;"         \
                            "}"                                       \


#define LineButtonStyleDotted "font: bold 15px;"               \
                             "border-left: 2px solid black;"    \
                             "padding-left: 8px;"                \
                             "border-style: dashed;"              \


#define LineButtonStyleSolid "font: bold 15px;"                \
                             "border-left: 2px solid black;"    \
                             "padding-left: 4px;"                \
                             "border-style: solid;"               \


#define QuitButtonStyle "QPushButton {"                  \
                        "    border-radius: 10px; "       \
                        "    color: white;"                \
                        "    background-color: #a30707;"    \
                        "    font: bold 15px;"               \
                        "    height: 29px;"                   \
                        "}"                                    \
                                                                \
                        "QPushButton:hover {"                    \
                        "    background-color: #c40c0c;"          \
                        "}"                                        \


#endif