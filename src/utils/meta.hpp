#pragma once
template <auto value>
concept IsConstexpr = requires {
    requires true;
};
