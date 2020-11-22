// ============= НАСТРОЙКИ =============
// -------- КНОПКА -------
#define USE_BUTTON 0    // 1 - использовать кнопку, 0 - нет

// -------- ВРЕМЯ -------
#define GMT 2              // смещение (москва 3)
#define NTP_ADDRESS  "europe.pool.ntp.org"    // сервер времени

// -------- РАССВЕТ -------
#define DAWN_BRIGHT 200       // макс. яркость рассвета
#define DAWN_TIMEOUT 1        // сколько рассвет светит после времени будильника, минут

// ---------- МАТРИЦА ---------
#define BRIGHTNESS 40         // стандартная маскимальная яркость (0-255)
#define CURRENT_LIMIT 2000    // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define WIDTH 7              // ширина матрицы
#define HEIGHT 7             // высота матрицы

#define COLOR_ORDER GRB       // порядок цветов на ленте. Если цвет отображается некорректно - меняйте. Начать можно с RGB

#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
// при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
// шпаргалка по настройке матрицы здесь! https://alexgyver.ru/matrix_guide/

// --------- ESP --------
#define ESP_MODE 1
// 0 - точка доступа
// 1 - локальный

// ----- AP (точка доступа) -------
#define AP_SSID "GyverLamp"
#define AP_PASS "12345678"
#define AP_PORT 8888

// -------- Менеджер WiFi ---------
#define AC_SSID "AutoConnectAP"
#define AC_PASS "12345678"

// ============= ДЛЯ РАЗРАБОТЧИКОВ =============
#define LED_PIN D4             // пин ленты
#define BTN_PIN D2
#define MODE_AMOUNT 18

#define NUM_LEDS WIDTH * HEIGHT
#define SEGMENTS 1            // диодов в одном "пикселе" (для создания матрицы из кусков ленты)
// ---------------- БИБЛИОТЕКИ -----------------
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define NTP_INTERVAL 60 * 1000    // обновление (1 минута)