# mysite/asgi.py
import os

from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.security.websocket import AllowedHostsOriginValidator
from django.core.asgi import get_asgi_application

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "django_project.settings")
django_asgi_app = get_asgi_application()

import accounts.routing
import pong.routing
import chat.routing

application = ProtocolTypeRouter(
    {
        "http": django_asgi_app,
        "websocket": AllowedHostsOriginValidator(
            AuthMiddlewareStack(
                URLRouter(
                    accounts.routing.websocket_urlpatterns +
                    chat.routing.websocket_urlpatterns +
                    pong.routing.websocket_urlpatterns
                )
            )
        ),
    }
)
